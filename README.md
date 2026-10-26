# Soulaima Bouhlel · Portfolio

A static, single-page portfolio. There is no build step, no framework and no server code: just HTML, CSS, JavaScript and media files.

```
soulaima-portfolio/
├── index.html            the whole site (styles, page, game, 3D viewer)
├── assets/
│   ├── room/             the Blender room for the browser (room.json + textures)
│   ├── game/             sprites used by the playable Shoot 'em up
│   └── *.mp4 *.webp …    renders, gameplay clip, screenshots
├── game-c-source/        the original C / MLV game (main.c, Makefile, images)
├── tools/                scripts used to convert room.blend for the web
└── .nojekyll             tells GitHub Pages to serve files as-is
```

Two pieces load from public CDNs, so the page needs an internet connection:
- three.js 0.160.0 (from cdn.jsdelivr.net) for the 3D room
- Google Fonts (Bricolage Grotesque, Instrument Sans, JetBrains Mono)

---

## 1. Run it on your computer

Don't double-click `index.html`. Browsers block `fetch()` on `file://` pages, so the 3D room won't load that way. Serve the folder through a small local web server instead.

**Option A, Python (already installed on most Linux/macOS machines):**

```bash
cd soulaima-portfolio
python3 -m http.server 8000
```
On Windows, use `py -m http.server 8000`.

Then open **http://localhost:8000** in your browser.

**Option B, Node.js:**

```bash
cd soulaima-portfolio
npx serve .
```
Then open the address it prints (usually http://localhost:3000).

**Option C, VS Code:** install the "Live Server" extension, right-click `index.html`, then choose **Open with Live Server**.

Check that everything works:
1. The hero video plays.
2. In **Projects → Play the Shoot 'em up**, click **▶ Play**. Use ← → to move, Space to fire, R to replay after game over, and O to go back to the title.
3. In **3D modeling & animation**, click **Load the room**. Try Orbit, Walk (W A S D / arrow keys) and the viewpoint buttons.

Press `Ctrl + C` in the terminal to stop the server.

---

## 2. Put it online for everyone

Any static host works. Here are three free options, from simplest to most flexible.

### Option 1: GitHub Pages (recommended, free, address: `https://soulaimabouhlel.github.io`)

1. Sign in to GitHub as **soulaimaBouhlel**.
2. Create a new **public** repository named exactly **`soulaimaBouhlel.github.io`**. Using this name makes it your main personal site.
3. Upload the files using one of these two methods:
   - **In the browser:** open the empty repo, click **uploading an existing file**, drag in *everything inside* `soulaima-portfolio/` (index.html, assets, game-c-source, tools, README.md), then click **Commit changes**.
     `.nojekyll` is hidden on some systems. If it didn't upload, click **Add file → Create new file**, name it `.nojekyll`, leave it empty, and commit.
   - **With git:**
     ```bash
     cd soulaima-portfolio
     git init
     git add .
     git commit -m "Portfolio"
     git branch -M main
     git remote add origin https://github.com/soulaimaBouhlel/soulaimaBouhlel.github.io.git
     git push -u origin main
     ```
4. In the repo, go to **Settings → Pages**. Under **Build and deployment**, choose **Source: Deploy from a branch**, **Branch: main**, folder **/ (root)**, then click **Save**.
5. Wait 1–3 minutes. The site will be live at **https://soulaimabouhlel.github.io**. The address also appears at the top of the Pages settings once it's ready.
6. To update the site later, edit the files and commit or push again. Pages redeploys automatically.

If you'd rather keep a different repo name (for example `portfolio`), the site will be at `https://soulaimabouhlel.github.io/portfolio/`. All paths in the site are relative, so that works too.

### Option 2: Netlify Drop (no account setup, about 1 minute)

1. Go to **https://app.netlify.com/drop**.
2. Drag the whole `soulaima-portfolio` folder onto the page.
3. Netlify gives you a public link right away, such as `https://random-name.netlify.app`. Sign up (free) to keep the site and rename it, for example `soulaima-bouhlel.netlify.app`, under **Site configuration → Change site name**.

### Option 3: Cloudflare Pages

1. Go to **dash.cloudflare.com → Workers & Pages → Create → Pages → Upload assets**.
2. Name the project (for example `soulaima-bouhlel`), drag in the folder, and click **Deploy**.
3. The site will be at `https://soulaima-bouhlel.pages.dev`.

### Optional: your own domain (for example soulaimabouhlel.com)

Buy the domain from any registrar (Namecheap, Porkbun, Cloudflare, …). Then:
- **GitHub Pages:** go to Settings → Pages → Custom domain and enter the domain. At your registrar, add the DNS records GitHub shows: four `A` records to 185.199.108.153, 185.199.109.153, 185.199.110.153 and 185.199.111.153, plus a `CNAME` record for `www` pointing to `soulaimabouhlel.github.io`. Then tick **Enforce HTTPS**.
- **Netlify / Cloudflare:** go to Domain management → Add a custom domain, and follow the DNS instructions shown.

### After it's live

- Open the link in a private/incognito window and on your phone to confirm the game and the 3D room work.
- Put the link in your CV header, your LinkedIn **Contact info → Website** and **Featured** sections, your GitHub profile, and your e-mail signature.
- Search engines will find the site on their own within a few days or weeks. To speed this up, add it in **Google Search Console** (https://search.google.com/search-console). The page already has a description and preview image for link sharing.

---

## 3. How the tricky parts work

**Playable game.** The game in `index.html` (the script block starting with `Shoot 'em up: JavaScript port`) is a line-by-line port of `game-c-source/main.c`. It uses the same 1280×800 field, sprite sizes, speeds (+0.5 px enemy, ±5 px ship, 10 px shots), hit boxes, half-second freeze after a kill, and five-miss game over. The C loop ran as fast as it could, about 90 frames per second, so the JavaScript runs a fixed 90 Hz simulation to keep the same pace on every screen. Two small additions: the score is shown during play, and on phones there are on-screen ◀ Fire ▶ buttons.

To build the original C version on Linux:

```bash
sudo apt install libmlv3-dev     # Ubuntu 24.04: download libmlv3 + libmlv3-dev .deb from archive.ubuntu.com/ubuntu/pool/universe/m/mlv/
cd game-c-source && make && ./main
```

**3D room.** `room.blend` (Blender 4.3) was exported with `tools/blender_export.py`. That script uses frame 480, so the laptop is open, applies modifiers, and decimates very dense meshes. The export was then compressed with glTF-Transform (WebP textures, quantized geometry) and packed by `tools/pack_room.mjs` into `assets/room/room.json` plus texture files. The page rebuilds the binary model in memory and hands it to three.js's GLTFLoader. The JSON packing exists because some hosts don't serve `.glb` files and block `data:` URLs; on a normal host it also works fine. Lights are placed where the Blender lights are, the laptop screen plays `laptop-screen.mp4`, and the glass is approximated because Cycles lighting can't run in real time.

To regenerate the model after editing the room in Blender:

```bash
pip install bpy==4.3.0 "numpy<2"           # needs Python 3.11
python tools/blender_export.py             # edit the .blend path at the top first
npx @gltf-transform/cli optimize room.glb room-web.glb --compress quantize \
    --texture-compress webp --texture-size 1024 --simplify false --palette false --join false
npm i @gltf-transform/core @gltf-transform/extensions
node tools/pack_room.mjs room-web.glb assets/room
```
