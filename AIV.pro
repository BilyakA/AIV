TEMPLATE = subdirs

SUBDIRS += \
    AIV \
    opencv

AIV.depends = opencv
