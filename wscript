# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# def options(opt):
#     pass

# def configure(conf):
#     conf.check_nonfatal(header_name='stdint.h', define_name='HAVE_STDINT_H')

def build(bld):
    model = bld.create_ns3_module('lisp', ['core'])
    model.source = [
       'model/lisp-header.cc',
       'helper/lisp-helper.cc',
       ]

    headers = bld(features='ns3header')
    headers.module = 'lisp'
    headers.source = [
        'model/lisp-header.h',
        'helper/lisp-helper.h',
        ]

    if bld.env.ENABLE_EXAMPLES:
        bld.recurse('examples')

     # bld.ns3_python_bindings()

