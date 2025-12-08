bl_info = {
    "name": "DuckyLib Model Exporter",
    "blender": (5, 0, 0),
    "category": "Import-Export",
}

import bpy
from bpy_extras.io_utils import ExportHelper
from bpy.types import Operator

class EXPORT_OT_dmdl(Operator, ExportHelper):
    bl_idname = "export_mesh.dmdl"
    bl_label = "Export DuckyLib Model"
    filename_ext = ".dmdl"
    
    filter_glob: bpy.props.StringProperty(default="*.dmdl", options={'HIDDEN'})

    def execute(self, context):
      obj = context.active_object
      if obj is None or obj.type != 'MESH':
        self.report({'ERROR'}, "No mesh selected")
        return {'CANCELLED'}

      mesh = obj.data
      has_uv = len(mesh.uv_layers) > 0
      uv_layer = mesh.uv_layers.active.data if has_uv else None
      vertices = []
      indices = []
      current_vertex_index = 0  

      for poly in mesh.polygons:
        idxs = []

        for loop_index in poly.loop_indices:
          loop = mesh.loops[loop_index]
          vert = mesh.vertices[loop.vertex_index]

          pos = obj.matrix_world @ vert.co
          vertices.extend([pos.x, pos.y, pos.z])

          if has_uv:
            uv = uv_layer[loop_index].uv
            vertices.extend([uv.x, uv.y])
          else:
            vertices.extend([0.0, 0.0])

          normal = loop.normal
          vertices.extend([normal.x, normal.y, normal.z])

          idxs.append(current_vertex_index)
          current_vertex_index += 1

        
        if len(idxs) == 4:  # quad
          indices.extend([idxs[0], idxs[2], idxs[1]])
          indices.extend([idxs[0], idxs[3], idxs[2]])
        elif len(idxs) == 3:  # triangle
          indices.extend([idxs[0], idxs[1], idxs[2]])



     
      with open(self.filepath, "w") as f:
          f.write(f"# DuckyLib Model (.dmdl)\n")
          f.write(f"vl {len(vertices)//8}\n"
                  f"il {len(indices)}\n")
          for i in range(0, len(vertices), 8):
              # order: x y z uv_x uv_y normal_x normal_y normal_z
              f.write(f"vp {vertices[i]} {vertices[i+2]} {vertices[i+1]}\n"
                      f"uv {vertices[i+3]} {vertices[i+4]}\n"
                      f"nrm {vertices[i+5] * -1} {vertices[i+6] * -1} {vertices[i+7] * -1}\n")

          for idx in indices:
              f.write(f"i {idx}\n")

      self.report({'INFO'}, f"Exported {obj.name} to {self.filepath}")
      return {'FINISHED'}

def menu_func_export(self, context):
    self.layout.operator(EXPORT_OT_dmdl.bl_idname, text="DuckyLib Model (.dmdl)")

def register():
    bpy.utils.register_class(EXPORT_OT_dmdl)
    bpy.types.TOPBAR_MT_file_export.append(menu_func_export)

def unregister():
    bpy.utils.unregister_class(EXPORT_OT_dmdl)
    bpy.types.TOPBAR_MT_file_export.remove(menu_func_export)

if __name__ == "__main__":
    register()
