"""Fresh camera/framing inputs for saved Blender inspection verification."""


def camera_framing(scene):
    camera = scene.camera
    if camera is None or camera.type != 'CAMERA':
        raise ValueError('inspection has no active camera')
    data, render = camera.data, scene.render
    return {
        'name': camera.name,
        'matrix_world': [list(row) for row in camera.matrix_world],
        'data': {key: getattr(data, key) for key in
                 ('type', 'ortho_scale', 'shift_x', 'shift_y', 'sensor_fit', 'clip_start', 'clip_end')},
        'depth_of_field': data.dof.use_dof,
        'render': {key: getattr(render, key) for key in
                   ('resolution_x', 'resolution_y', 'resolution_percentage', 'pixel_aspect_x', 'pixel_aspect_y',
                    'use_border', 'use_crop_to_border', 'border_min_x', 'border_max_x', 'border_min_y', 'border_max_y')},
    }
