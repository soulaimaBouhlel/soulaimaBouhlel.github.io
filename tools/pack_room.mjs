import {NodeIO} from '@gltf-transform/core';
import {ALL_EXTENSIONS} from '@gltf-transform/extensions';
import fs from 'fs'; import path from 'path';
const [src,outDir]=process.argv.slice(2);
fs.rmSync(outDir,{recursive:true,force:true}); fs.mkdirSync(outDir,{recursive:true});
const io=new NodeIO().registerExtensions(ALL_EXTENSIONS);
const doc=await io.read(src);
// give textures clean unique names
doc.getRoot().listTextures().forEach((t,i)=>{ t.setURI(`tex${i}.webp`); });
const {json,resources}=await io.writeJSON(doc,{format:'json',basename:'room'});
let bin=null;
for(const [uri,data] of Object.entries(resources)){
  if(uri.endsWith('.bin')) bin=Buffer.from(data);
  else fs.writeFileSync(path.join(outDir,uri),Buffer.from(data));
}
if(json.buffers.length!==1) throw new Error('expected one buffer');
delete json.buffers[0].uri;
fs.writeFileSync(path.join(outDir,'room.json'),JSON.stringify({gltf:json,bin:bin.toString('base64')}));
console.log('images',(json.images||[]).map(i=>i.uri).join(','),'bin',bin.length);
