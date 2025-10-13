project('charm', 'cpp')

cmake = import('cmake')

itk_cmake_options = cmake.subproject_options()
itk_cmake_options.add_cmake_defines({
                                        'BUILD_SHARED_LIBS' : 'OFF',
                                        'BUILD_TESTING' : 'OFF',
                                        'BUILD_EXAMPLES' : 'OFF',
                                        'ITKV4_COMPATIBILITY': 'ON',
                                        'ITK_LEGACY_REMOVE': 'OFF',
                                        'ITK_USE_SYSTEM_HDF5': 'ON',
                                        'ITK_USE_SYSTEM_ZLIB': 'ON'
                                    })

itk_subproject = cmake.subproject('ITK', options : itk_cmake_options)
itk_deps = [
    itk_subproject.dependency('ITKCommon'),
    itk_subproject.dependency('ITKMesh'),
    itk_subproject.dependency('ITKImageFeature'),
    itk_subproject.dependency('ITKImageIntensity'),
    itk_subproject.dependency('ITKOptimizers'),
    itk_subproject.dependency('ITKOptimizersv4'),
    itk_subproject.dependency('ITKRegistrationMethodsv4'),
    itk_subproject.dependency('ITKTransform'),
    itk_subproject.dependency('ITKIOImageBase')
]

zlib_dep = dependency('zlib', fallback: ['zstd', 'zstd_dep'])

libgzstream = library('gzstream', ['src/charm/gzstream.h', 'src/charm/gzstream.C'], dependencies: [zlib_dep])

use_dynamic_mesh = get_option('use_dynamic_mesh')

if use_dynamic_mesh
    add_global_arguments('-DUSE_DYNAMIC_MESH', language: 'cpp')
endif

charm_sources = [
    'src/charm/kvlAtlasMeshCollectionValidator.cxx',
    'src/charm/stopwatch.hpp',
    # 'src/charm/gzstream.h',
    'src/charm/kvlAtlasMeshDeformationFixedStepGradientDescentOptimizer.cxx',
    'src/charm/kvlAtlasMeshProbabilityImageStatisticsCollector.cxx',
    'src/charm/kvlAtlasMeshMultiAlphaDrawer.h',
    'src/charm/kvlParameterOrderPowellOptimizer.h',
    'src/charm/kvlAtlasMeshToPointSetCostAndGradientCalculator.cxx',
    'src/charm/kvlAtlasMeshProbabilityImageStatisticsCollector.h',
    'src/charm/kvlAtlasMeshToIntensityImageCostAndGradientCalculator.cxx',
    'src/charm/kvlRegisterImages.hxx',
    'src/charm/kvlAtlasMeshDeformationConjugateGradientOptimizer.cxx',
    # 'src/charm/gzstream.C',
    'src/charm/kvlAtlasMeshToPointSetCostAndGradientCalculator.h',
    'src/charm/kvlAtlasMeshRasterizor.h',
    'src/charm/kvlAtlasMeshStatisticsCollector.cxx',
    'src/charm/kvlAtlasParameterEstimator.h',
    'src/charm/kvlAtlasMeshDeformationFixedStepGradientDescentOptimizer.h',
    'src/charm/kvlTetrahedronInteriorIterator.hxx',
    'src/charm/kvlAtlasMeshDeformationGradientDescentOptimizer.cxx',
    'src/charm/kvlAverageAtlasMeshPositionCostAndGradientCalculator.h',
    'src/charm/kvlAtlasMeshPositionCostAndGradientCalculator.h',
    'src/charm/itkMGHImageIOFactory.h',
    'src/charm/kvlCompressionLookupTable.h',
    'src/charm/kvlAtlasMeshJacobianDeterminantDrawer.cxx',
    'src/charm/kvlGMMLikelihoodImageFilter.h',
    'src/charm/kvlHistogrammer.h',
    'src/charm/kvlAtlasMeshLabelImageStatisticsCollector.cxx',
    'src/charm/kvlAtlasMeshSummaryDrawer.h',
    'src/charm/kvlAtlasMeshToLabelImageCostAndGradientCalculator.h',
    'src/charm/kvlAtlasMeshDeformationGradientDescentOptimizer.h',
    'src/charm/kvlAtlasMeshVisitCounter.cxx',
    'src/charm/kvlAtlasMeshDeformationConjugateGradientOptimizer.h',
    'src/charm/kvlAtlasMeshRasterizor.cxx',
    'src/charm/kvlAtlasMeshMultiAlphaDrawer.cxx',
    'src/charm/kvlAtlasMeshAlphaDrawer.cxx',
    'src/charm/kvlAtlasMeshPositionCostAndGradientCalculator.cxx',
    'src/charm/kvlMutualInformationCostAndGradientCalculator.h',
    'src/charm/kvlAtlasMeshCollection.h',
    'src/charm/kvlCroppedImageReader.cxx',
    'src/charm/kvlAtlasParameterEstimator.cxx',
    'src/charm/kvlAverageAtlasMeshPositionCostAndGradientCalculator.cxx',
    'src/charm/kvlAtlasMeshAlphaDrawer.h',
    'src/charm/kvlAtlasMeshSmoother.h',
    'src/charm/kvlAtlasMeshLabelImageStatisticsCollector.h',
    'src/charm/kvlCroppedImageReader.h',
    'src/charm/itkMGHImageIO.cxx',
    'src/charm/itkMGHImageIOFactory.cxx',
    'src/charm/kvlCompressionLookupTable.cxx',
    'src/charm/kvlAtlasMeshSmoother.cxx',
    'src/charm/kvlAtlasMeshDeformationOptimizer.cxx',
    'src/charm/kvlTetrahedronAspectRatio.h',
    'src/charm/kvlMutualInformationCostAndGradientCalculator.cxx',
    'src/charm/kvlAtlasMeshDeformationLBFGSOptimizer.cxx',
    'src/charm/itkMGHImageIO.h',
    'src/charm/ITKFactoryRegistration/itkTransformIOFactoryRegisterManager.h',
    'src/charm/ITKFactoryRegistration/itkImageIOFactoryRegisterManager.h',
    'src/charm/kvlTetrahedronInteriorIterator.h',
    'src/charm/kvlGMMLikelihoodImageFilter.hxx',
    'src/charm/kvlAtlasMeshCollectionValidator.h',
    'src/charm/kvlTetrahedronInteriorConstIterator.hxx',
    'src/charm/kvlAtlasMeshCollection.cxx',
    'src/charm/kvlConditionalGaussianEntropyCostAndGradientCalculator.h',
    'src/charm/kvlAtlasMeshToIntensityImageCostAndGradientCalculator.h',
    'src/charm/interfaces/atlasmeshalphadrawer.hpp',
    'src/charm/interfaces/atlasmeshvisitcounter.hpp',
    'src/charm/kvlHistogrammer.cxx',
    'src/charm/kvlAtlasMeshValueDrawer.h',
    'src/charm/kvlAtlasMeshSummaryDrawer.cxx',
    'src/charm/kvlTetrahedronInteriorConstIterator.h',
    'src/charm/kvlAtlasMeshDeformationLBFGSOptimizer.h',
    'src/charm/kvlAtlasMesh.h',
    'src/charm/kvlConditionalGaussianEntropyCostAndGradientCalculator.cxx',
    'src/charm/kvlAtlasMeshStatisticsCollector.h',
    'src/charm/kvlAtlasMeshToLabelImageCostAndGradientCalculator.cxx',
    'src/charm/kvlAtlasMeshVisitCounter.h',
    'src/charm/kvlAtlasMeshValueDrawer.cxx',
    'src/charm/kvlAtlasMeshDeformationOptimizer.h',
    'src/charm/kvlAtlasMeshMinLogLikelihoodCalculator.h',
    'src/charm/kvlAtlasMeshJacobianDeterminantDrawer.h',
    'src/charm/kvlRegisterImages.h'
]

libcharm = library('charm', charm_sources, dependencies : [] + itk_deps, link_with: [libgzstream])
