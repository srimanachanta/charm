#ifndef __kvlAtlasMeshPositionCostAndGradientCalculator_h
#define __kvlAtlasMeshPositionCostAndGradientCalculator_h

#include "itkAffineTransform.h"
#include "kvlAtlasMeshRasterizor.h"

#define KVL_ENABLE_TIME_PROBE 0

#if KVL_ENABLE_TIME_PROBE
#include "itkTimeProbe.h"
#endif

namespace kvl {

/**
 *
 */
class AtlasMeshPositionCostAndGradientCalculator : public AtlasMeshRasterizor {
 public:
  /** Standard class typedefs */
  typedef AtlasMeshPositionCostAndGradientCalculator Self;
  typedef AtlasMeshRasterizor Superclass;
  typedef itk::SmartPointer<Self> Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(AtlasMeshPositionCostAndGradientCalculator, AtlasMeshRasterizor);

  /** Some typedefs */
  typedef itk::AffineTransform<double, 3> TransformType;

  /** */
  void SetMeshToImageTransform(const TransformType* meshToImageTransform);

  /** */
  void SetIgnoreDeformationPrior(bool ignoreDeformationPrior) {
    m_IgnoreDeformationPrior = ignoreDeformationPrior;
  }

  /** */
  void SetOnlyDeformationPrior(bool onlyDeformationPrior) {
    m_OnlyDeformationPrior = onlyDeformationPrior;
  }

  /** */
  const AtlasPositionGradientContainerType* GetPositionGradient() const {
    return m_PositionGradient;
  }

  /** */
  AtlasPositionGradientContainerType* GetPositionGradient() {
    return m_PositionGradient;
  }

  /** */
  double GetMinLogLikelihoodTimesPrior() const {
    return m_MinLogLikelihoodTimesPrior;
  }

  /** */
  double& GetMinLogLikelihoodTimesPrior() {
    return m_MinLogLikelihoodTimesPrior;
  }

  /** */
  void Rasterize(const AtlasMesh* mesh);

  /**  Boundary conditions applied to gradient */
  enum BoundaryConditionType { NONE, SLIDING, AFFINE, TRANSLATION };
  void SetBoundaryCondition(const BoundaryConditionType& boundaryCondition) {
    m_BoundaryCondition = boundaryCondition;
  }

  const BoundaryConditionType& GetBoundaryCondition() const {
    return m_BoundaryCondition;
  }

 protected:
  AtlasMeshPositionCostAndGradientCalculator();
  virtual ~AtlasMeshPositionCostAndGradientCalculator();

  //
  bool RasterizeTetrahedron(const AtlasMesh* mesh,
                            AtlasMesh::CellIdentifier tetrahedronId,
                            int threadNumber);

  virtual void AddDataContributionOfTetrahedron(
      const AtlasMesh::PointType& p0, const AtlasMesh::PointType& p1,
      const AtlasMesh::PointType& p2, const AtlasMesh::PointType& p3,
      const AtlasAlphasType& alphasInVertex0,
      const AtlasAlphasType& alphasInVertex1,
      const AtlasAlphasType& alphasInVertex2,
      const AtlasAlphasType& alphasInVertex3, double& priorPlusDataCost,
      AtlasPositionGradientType& gradientInVertex0,
      AtlasPositionGradientType& gradientInVertex1,
      AtlasPositionGradientType& gradientInVertex2,
      AtlasPositionGradientType& gradientInVertex3) {}

  virtual bool AddPriorContributionOfTetrahedron(
      const AtlasMesh::PointType& p0, const AtlasMesh::PointType& p1,
      const AtlasMesh::PointType& p2, const AtlasMesh::PointType& p3,
      const ReferenceTetrahedronInfo& info, double& priorPlusDataCost,
      AtlasPositionGradientType& gradientInVertex0,
      AtlasPositionGradientType& gradientInVertex1,
      AtlasPositionGradientType& gradientInVertex2,
      AtlasPositionGradientType& gradientInVertex3);

  // Let's provide a "hook" for adding non-tetrahdron-based cost and gradient
  // contributions
  virtual void PostProcessCostAndGradient(const AtlasMesh* mesh) {}

  //
  void ImposeSlidingBoundaryConditions(const AtlasMesh* mesh);

  //
  void ImposeAffineBoundaryConditions(const AtlasMesh* mesh);

  //
  void ImposeTranslationBoundaryConditions(const AtlasMesh* mesh);

  //
  void ImposeBoundaryCondition(const AtlasMesh* mesh);

  //
  AtlasPositionGradientContainerType::Pointer m_PositionGradient;
  bool m_IgnoreDeformationPrior;
  bool m_OnlyDeformationPrior;
  double m_MinLogLikelihoodTimesPrior;
  bool m_Abort;
  BoundaryConditionType m_BoundaryCondition;

  //
  vnl_matrix<double> m_AffineProjectionMatrix;

 private:
  AtlasMeshPositionCostAndGradientCalculator(
      const Self&);             // purposely not implemented
  void operator=(const Self&);  // purposely not implemented

  //
  typedef itk::Matrix<double> SlidingBoundaryCorrectionMatrixType;
  SlidingBoundaryCorrectionMatrixType m_SlidingBoundaryCorrectionMatrices[8];

  //
  std::vector<AtlasPositionGradientContainerType::Pointer>
      m_ThreadSpecificPositionGradients;
  std::vector<double> m_ThreadSpecificMinLogLikelihoodTimesPriors;

#if KVL_ENABLE_TIME_PROBE
  //
  std::vector<itk::TimeProbe> m_ThreadSpecificDataTermRasterizationTimers;
  std::vector<itk::TimeProbe> m_ThreadSpecificPriorTermRasterizationTimers;
  std::vector<itk::TimeProbe> m_ThreadSpecificOtherRasterizationTimers;

#endif
};

}  // end namespace kvl

#endif
