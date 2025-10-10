project('charm', 'cpp')

cmake = import('cmake')

itk_cmake_options = cmake.subproject_options()

itk_cmake_options.add_cmake_defines({
                                        'BUILD_SHARED_LIBS' : 'OFF',
                                        'BUILD_TESTING' : 'OFF',
                                        'BUILD_EXAMPLES' : 'OFF'
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
]

libcharm = library('charm', 'src/charm/cpp/lib.cpp', dependencies : [] + itk_deps)

executable('charm_cli', 'src/charm_cli/cpp/main.cpp', link_with : [libcharm])
