set(ITK_OLDEST_VALIDATED_POLICIES_VERSION "3.16.3")
set(ITK_NEWEST_VALIDATED_POLICIES_VERSION "3.29.0")
cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)
project(charm LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

set(BUILD_SHARED_LIBS OFF)
set(BUILD_TESTING OFF)
set(BUILD_EXAMPLES OFF)

# Build ITK from source, then immediately run find_package on the build output.
# This is required to execute ITK's configuration scripts, which populate the variables needed for linking.
add_subdirectory(ITK)
set(ITK_DIR ${ITK_BINARY_DIR})
find_package(ITK 5.4.4 REQUIRED)

set(CHARM_SOURCES
        src/charm/kvlMutualInformationCostAndGradientCalculator.h
        src/charm/kvlAtlasMeshProbabilityImageStatisticsCollector.cxx
        src/charm/kvlAtlasMeshDeformationFixedStepGradientDescentOptimizer.cxx
        src/charm/kvlAtlasMeshMultiAlphaDrawer.h
        src/charm/kvlAverageAtlasMeshPositionCostAndGradientCalculator.h
        src/charm/kvlAtlasMeshDeformationConjugateGradientOptimizer.cxx
        src/charm/kvlConditionalGaussianEntropyCostAndGradientCalculator.h
        src/charm/kvlAtlasMeshToPointSetCostAndGradientCalculator.h
        src/charm/kvlAtlasMeshProbabilityImageStatisticsCollector.h
        src/charm/kvlAtlasMeshToLabelImageCostAndGradientCalculator.cxx
        src/charm/kvlCroppedImageReader.cxx
        src/charm/kvlAtlasMeshSummaryDrawer.cxx
        src/charm/kvlRegisterImages.hxx
        src/charm/kvlAtlasMeshAlphaDrawer.h
        src/charm/kvlCompressionLookupTable.cxx
        src/charm/kvlAtlasMeshStatisticsCollector.cxx
        src/charm/stopwatch.hpp
        src/charm/kvlTetrahedronInteriorConstIterator.h
        src/charm/kvlAtlasMeshRasterizor.cxx
        src/charm/kvlAtlasMeshAlphaDrawer.cxx
        src/charm/kvlAtlasMeshSmoother.cxx
        src/charm/kvlAtlasMeshDeformationGradientDescentOptimizer.cxx
        src/charm/kvlMutualInformationCostAndGradientCalculator.cxx
        src/charm/kvlAtlasMeshLabelImageStatisticsCollector.cxx
        src/charm/itkMGHImageIO.h
        src/charm/kvlAtlasMeshRasterizor.h
        src/charm/kvlAverageAtlasMeshPositionCostAndGradientCalculator.cxx
        src/charm/kvlTetrahedronInteriorIterator.hxx
        src/charm/kvlAtlasMeshCollection.h
        src/charm/kvlConditionalGaussianEntropyCostAndGradientCalculator.cxx
        src/charm/kvlAtlasMeshValueDrawer.h
        src/charm/kvlAtlasMeshStatisticsCollector.h
        src/charm/kvlHistogrammer.h
        src/charm/kvlAtlasMeshMultiAlphaDrawer.cxx
        src/charm/kvlCompressionLookupTable.h
        src/charm/kvlAtlasMeshJacobianDeterminantDrawer.h
        src/charm/kvlAtlasMeshToLabelImageCostAndGradientCalculator.h
        src/charm/gzstream.C
        src/charm/kvlAtlasMeshDeformationOptimizer.h
        src/charm/kvlGMMLikelihoodImageFilter.hxx
        src/charm/kvlAtlasMeshSmoother.h
        src/charm/kvlAtlasMeshPositionCostAndGradientCalculator.h
        src/charm/kvlGMMLikelihoodImageFilter.h
        src/charm/kvlAtlasParameterEstimator.cxx
        src/charm/kvlAtlasMeshDeformationGradientDescentOptimizer.h
        src/charm/kvlAtlasMeshDeformationFixedStepGradientDescentOptimizer.h
        src/charm/kvlRegisterImages.h
        src/charm/kvlTetrahedronInteriorConstIterator.hxx
        src/charm/kvlAtlasMeshSummaryDrawer.h
        src/charm/kvlAtlasMeshVisitCounter.cxx
        src/charm/kvlAtlasMeshDeformationOptimizer.cxx
        src/charm/kvlAtlasMeshToIntensityImageCostAndGradientCalculator.h
        src/charm/kvlAtlasParameterEstimator.h
        src/charm/itkMGHImageIO.cxx
        src/charm/kvlAtlasMeshLabelImageStatisticsCollector.h
        src/charm/kvlHistogrammer.cxx
        src/charm/kvlAtlasMeshValueDrawer.cxx
        src/charm/kvlTetrahedronInteriorIterator.h
        src/charm/kvlAtlasMeshDeformationLBFGSOptimizer.cxx
        src/charm/kvlAtlasMeshDeformationLBFGSOptimizer.h
        src/charm/kvlAtlasMeshCollectionValidator.h
        src/charm/kvlCroppedImageReader.h
        src/charm/kvlAtlasMeshVisitCounter.h
        src/charm/kvlAtlasMeshToIntensityImageCostAndGradientCalculator.cxx
        src/charm/ITKFactoryRegistration/itkTransformIOFactoryRegisterManager.h
        src/charm/ITKFactoryRegistration/itkImageIOFactoryRegisterManager.h
        src/charm/kvlAtlasMeshToPointSetCostAndGradientCalculator.cxx
        src/charm/kvlAtlasMeshPositionCostAndGradientCalculator.cxx
        src/charm/kvlAtlasMeshJacobianDeterminantDrawer.cxx
        src/charm/kvlTetrahedronAspectRatio.h
        src/charm/kvlParameterOrderPowellOptimizer.h
        src/charm/kvlAtlasMeshCollectionValidator.cxx
        src/charm/kvlAtlasMeshMinLogLikelihoodCalculator.h
        src/charm/kvlAtlasMeshCollection.cxx
        src/charm/kvlAtlasMesh.h
        src/charm/kvlAtlasMeshDeformationConjugateGradientOptimizer.h
        src/charm/gzstream.h
        src/charm/itkMGHImageIOFactory.h
        src/charm/itkMGHImageIOFactory.cxx
        src/charm/interfaces/atlasmeshvisitcounter.hpp
        src/charm/interfaces/atlasmeshalphadrawer.hpp
)

option(USE_DYNAMIC_MESH "Use dynamic mesh instead of static" OFF)

add_library(charm ${CHARM_SOURCES})
target_include_directories(charm PRIVATE ${ITK_INCLUDE_DIRS})
target_link_libraries(charm PRIVATE ${ITK_LIBRARIES})

set(MESH_TYPE "Static")

if(USE_DYNAMIC_MESH)
  set(MESH_TYPE "Dynamic")
  target_compile_definitions(charm PRIVATE USE_DYNAMIC_MESH)
endif()

message(STATUS "Mesh Type: ${MESH_TYPE}")
