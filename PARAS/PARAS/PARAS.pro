cache()

QT += core \
    gui \
    opengl
CONFIG += c++11
HEADERS += \
    src/util/Convert.hpp \
    src/util/Utility.hpp \
    src/paras/Attribute.hpp \
    src/paras/PARAS.hpp \
    src/paras/PSpaceGenerator.hpp \
    src/paras/PSpaceIndex.hpp \
    src/paras/Rule.hpp \
    src/paras/XYPair.hpp \
    src/graphical/EventController.hpp \
    src/graphical/EventListener.hpp \
    src/graphical/GUI.hpp \
    src/graphical/GUIEventObject.h \
    src/graphical/IndexUpdateEvent.hpp \
    src/graphical/PSpaceGraph.hpp \
    src/graphical/StableRegion.hpp \
    src/graphical/ruleview/doublerule/DoubleRuleTable.hpp \
    src/graphical/ruleview/singlerule/glyph/Glyph.hpp \
    src/graphical/ruleview/singlerule/FilterCompleter.hpp \
    src/graphical/ruleview/singlerule/FilterEditor.hpp \
    src/graphical/ruleview/singlerule/SingleRuleTable.hpp \
    src/graphical/color/ColorAssign.h \
    src/graphical/color/ColorMacros.h \
    src/graphical/color/ColorManager.h \
    src/graphical/color/ColorMap.h \
    src/graphical/color/ColorRamp.h \
    src/graphical/color/ColorSelector.h \
    src/graphical/color/Image.h \
    src/graphical/color/RGBt.h \
    src/graphical/color/Vec2.h \
    src/graphical/color/Vec3.h \
    src/graphical/ruleview/RuleView.hpp \
    src/graphical/ruleview/singlerule/glyph/GlyphDisplay.hpp \
    src/graphical/ruleview/singlerule/glyph/GlyphView.hpp \
    src/graphical/ruleview/singlerule/glyph/GlyphZoom.hpp \
    src/util/json/json_batchallocator.h \
    src/util/json/writer.h \
    src/util/json/value.h \
    src/util/json/reader.h \
    src/util/json/json.h \
    src/util/json/forwards.h \
    src/util/json/features.h \
    src/util/json/config.h \
    src/util/json/autolink.h \
    src/graphical/ruleview/singlerule/SingleView.hpp \
    src/graphical/ruleview/singlerule/RuleDetailView.hpp \
    src/apriori/Trie.hpp \
    src/apriori/Input_Output_Manager.hpp \
    src/apriori/common.hpp \
    src/apriori/Apriori.hpp \
    src/apriori/Apriori_Trie.hpp \
    src/paras/PreProcessor.hpp \
    src/graphical/CreateIndexDialog.h \
    src/graphical/CreateIndexPreview.h \
    src/util/mds/nrutil.h \
    src/util/mds/Multidimensional_scaling.h \
    src/util/mds/MDS_misc.h \
    src/util/mds/MDS_Kruskal.h \
    src/util/mds/MDS_Embedding.h \
    src/util/mds/IP_Vector.h \
    src/util/mds/IP_Matrix.h \
    src/util/mds/IP_Array.h \
    src/util/pca/PCA.h \
    src/graphical/CreateIndexDialogBasket.h

SOURCES += \
    src/util/Convert.cpp \
    src/util/Utility.cpp \
    src/paras/Attribute.cpp \
    src/paras/PARAS.cpp \
    src/paras/PSpaceGenerator.cpp \
    src/paras/PSpaceIndex.cpp \
    src/paras/Rule.cpp \
    src/paras/XYPair.cpp \
    src/graphical/EventController.cpp \
    src/graphical/GUI.cpp \
    src/graphical/pspacegraph.cpp \
    src/graphical/stableregion.cpp \
    src/graphical/StartupGUI.cpp \
    src/graphical/ruleview/doublerule/DoubleRuleTable.cpp \
    src/graphical/ruleview/singlerule/FilterCompleter.cpp \
    src/graphical/ruleview/singlerule/FilterEditor.cpp \
    src/graphical/ruleview/singlerule/SingleRuleTable.cpp \
    src/graphical/color/ColorManager.cpp \
    src/graphical/color/ColorMap.cpp \
    src/graphical/color/ColorRamp.cpp \
    src/graphical/color/ColorSelector.cpp \
    src/graphical/color/Image.cpp \
    src/graphical/ruleview/RuleView.cpp \
    src/util/json/json_writer.cpp \
    src/util/json/json_valueiterator.inl \
    src/util/json/json_value.cpp \
    src/util/json/json_reader.cpp \
    src/util/json/json_internalmap.inl \
    src/util/json/json_internalarray.inl \
    src/graphical/ruleview/singlerule/glyph/GlyphZoom.cpp \
    src/graphical/ruleview/singlerule/glyph/GlyphView.cpp \
    src/graphical/ruleview/singlerule/glyph/GlyphDisplay.cpp \
    src/graphical/ruleview/singlerule/glyph/Glyph.cpp \
    src/graphical/ruleview/singlerule/SingleView.cpp \
    src/graphical/ruleview/singlerule/RuleDetailView.cpp \
    src/apriori/Trie.cpp \
    src/apriori/Input_Output_Manager.cpp \
    src/apriori/Apriori.cpp \
    src/apriori/Apriori_Trie.cpp \
    src/paras/PreProcessor.cpp \
    src/graphical/CreateIndexDialog.cpp \
    src/graphical/CreateIndexPreview.cpp \
    src/util/mds/nrutil.c \
    src/util/mds/Multidimensional_scaling.cpp \
    src/util/mds/MDS_Kruskal.cpp \
    src/util/mds/MDS_Embedding.cpp \
    src/util/pca/PCA.cpp \
    src/graphical/CreateIndexDialogBasket.cpp

INCLUDEPATH += src

OTHER_FILES += \
    src/util/json/sconscript
