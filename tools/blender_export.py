"""Export the bedroom scene from room.blend to a web-ready GLB.

Run with Blender's Python module (pip install bpy==4.3.0 "numpy<2", Python 3.11):
    python tools/blender_export.py
or inside Blender:  blender -b room.blend --python tools/blender_export.py
"""
import bpy

# Edit these two paths for your machine
BLEND_FILE = 'projet/room.blend'
OUT_GLB = 'room.glb'

bpy.ops.wm.open_mainfile(filepath=BLEND_FILE)
sc = bpy.data.scenes['Scene']
bpy.context.window.scene = sc
sc.frame_set(480)                      # laptop is open at this frame
vl = sc.view_layers[0]

keep = []
for o in sc.objects:
    o.select_set(False)
    visible = o.visible_get(view_layer=vl) and not o.hide_render
    if visible and o.type in ('MESH', 'CURVE', 'EMPTY') and o.matrix_world.translation.y > -8 \
            and o.name != 'Plane.002':
        o.select_set(True)
        keep.append(o.name)

# Decimate very dense meshes so the browser download stays small
dg = bpy.context.evaluated_depsgraph_get()
for name in keep:
    o = bpy.data.objects[name]
    if o.type != 'MESH':
        continue
    n = len(o.evaluated_get(dg).data.vertices)
    if n > 3000:
        m = o.modifiers.new('web_decimate', 'DECIMATE')
        m.ratio = max(0.08, 3000 / n)

bpy.ops.export_scene.gltf(
    filepath=OUT_GLB, export_format='GLB', use_selection=True,
    export_apply=True, export_yup=True,
    export_image_format='JPEG', export_jpeg_quality=80,
    export_animations=False, export_current_frame=True,
    export_lights=False, export_cameras=False,
)
print('Exported', len(keep), 'objects to', OUT_GLB)
