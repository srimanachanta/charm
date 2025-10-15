#ifndef __kvlAtlasMeshToIntensityImageCostAndGradientCalculator_h
#define __kvlAtlasMeshToIntensityImageCostAndGradientCalculator_h

#include "itkImage.h"
#include "kvlAtlasMeshPositionCostAndGradientCalculator.h"
#include "kvlGMMLikelihoodImageFilter.h"

namespace kvl {

/**
 *
 */
class AtlasMeshToIntensityImageCostAndGradientCalculator
    : public AtlasMeshPositionCostAndGradientCalculator {
 public:
  /** Standard class typedefs */
  typedef AtlasMeshToIntensityImageCostAndGradientCalculator Self;
  typedef AtlasMeshPositionCostAndGradientCalculator Superclass;
  typedef itk::SmartPointer<Self> Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(AtlasMeshToIntensityImageCostAndGradientCalculator,
               AtlasMeshPositionCostAndGradientCalculator);

  /** Some typedefs */
  typedef itk::Image<float, 3> ImageType;

  /** */
  void SetImages(const std::vector<ImageType::ConstPointer>& images);

  /** */
  void SetParameters(const std::vector<vnl_vector<double> >& means,
                     const std::vector<vnl_matrix<double> >& variances,
                     const std::vector<double>& mixtureWeights,
                     const std::vector<int>& numberOfGaussiansPerClass);

  /** */
  void Rasterize(const AtlasMesh* mesh) override;

 protected:
  AtlasMeshToIntensityImageCostAndGradientCalculator();
  virtual ~AtlasMeshToIntensityImageCostAndGradientCalculator();

  void AddDataContributionOfTetrahedron(
      const AtlasMesh::PointType& p0, const AtlasMesh::PointType& p1,
      const AtlasMesh::PointType& p2, const AtlasMesh::PointType& p3,
      const AtlasAlphasType& alphasInVertex0,
      const AtlasAlphasType& alphasInVertex1,
      const AtlasAlphasType& alphasInVertex2,
      const AtlasAlphasType& alphasInVertex3, double& priorPlusDataCost,
      AtlasPositionGradientType& gradientInVertex0,
      AtlasPositionGradientType& gradientInVertex1,
      AtlasPositionGradientType& gradientInVertex2,
      AtlasPositionGradientType& gradientInVertex3) override;

 private:
  AtlasMeshToIntensityImageCostAndGradientCalculator(
      const Self&);             // purposely not implemented
  void operator=(const Self&);  // purposely not implemented

  //
  typedef GMMLikelihoodImageFilter<ImageType> LikelihoodFilterType;
  LikelihoodFilterType::Pointer m_LikelihoodFilter;
};

}  // end namespace kvl

#endif
