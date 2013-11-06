TEMPLATE = subdirs
SUBDIRS = common life_source life_gui_source
life_source.depends = common
life_gui_source.depends = common
