"""Shared admission of explicitly selected material inspection artifacts."""
from pathlib import Path


def texgen_options(options, root):
    if (not isinstance(options, dict) or set(options) not in ({'output'}, {'output', 'mode'})
            or not isinstance(options['output'], str) or not options['output']):
        raise ValueError('texgen inspection requires an output path and optional mode')
    mode = options.get('mode', 'neutral')
    if mode not in ('neutral', 'animated'):
        raise ValueError('texgen inspection mode must be neutral or animated')
    root = Path(root).resolve()
    destination = (root / options['output']).resolve()
    build = (root / 'build').resolve()
    if not destination.is_relative_to(build) or destination == build:
        raise ValueError('texgen inspection artifact must be a child of build/')
    return mode, destination


def scene55_output(options, root):
    if (not isinstance(options, dict) or set(options) != {'output'}
            or not isinstance(options['output'], str) or not options['output']):
        raise ValueError('scene55 inspection requires one artifact output path')
    root = Path(root).resolve()
    destination = (root / options['output']).resolve()
    build = (root / 'build').resolve()
    if not destination.is_relative_to(build) or destination == build:
        raise ValueError('scene55 inspection artifact must be a child of build/')
    return destination


def embedded_type13_output(options, root):
    if (not isinstance(options, dict) or set(options) != {'output'}
            or not isinstance(options['output'], str) or not options['output']):
        raise ValueError('embedded type13 inspection requires one artifact output path')
    root = Path(root).resolve()
    destination = (root / options['output']).resolve()
    build = (root / 'build').resolve()
    if not destination.is_relative_to(build) or destination == build:
        raise ValueError('embedded type13 inspection must be a child of build/')
    return destination


def haybot_output(options, root):
    if (not isinstance(options, dict) or set(options) != {'output'}
            or not isinstance(options['output'], str) or not options['output']):
        raise ValueError('Haybot inspection requires one artifact output path')
    root = Path(root).resolve()
    destination = (root / options['output']).resolve()
    build = (root / 'build').resolve()
    if not destination.is_relative_to(build) or destination == build:
        raise ValueError('Haybot inspection must be a child of build/')
    return destination


def embedded_type06_output(options, root):
    if (not isinstance(options, dict) or set(options) != {'output'}
            or not isinstance(options['output'], str) or not options['output']):
        raise ValueError('embedded type06 inspection requires one artifact output path')
    root = Path(root).resolve()
    destination = (root / options['output']).resolve()
    build = (root / 'build').resolve()
    if not destination.is_relative_to(build) or destination == build:
        raise ValueError('embedded type06 inspection must be a child of build/')
    return destination
