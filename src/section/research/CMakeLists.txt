add_library(
    sectionResearch

    ResearchCategory.cpp
    ResearchCategory.h

    ResearchTier.cpp
    ResearchTier.h
)

target_include_directories(sectionResearch PRIVATE util)