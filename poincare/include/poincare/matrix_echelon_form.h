#ifndef POINCARE_MATRIX_ECHELON_FORM_H
#define POINCARE_MATRIX_ECHELON_FORM_H

#include <poincare/expression.h>

namespace Poincare {

class MatrixEchelonFormNode : public ExpressionNode {
public:

  // TreeNode
  int numberOfChildren() const override;
  virtual bool isFormReduced() const = 0;
  static constexpr int sNumberOfChildren = 1;
private:
  // Layout
  Layout createLayout(Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override;
  int serialize(char * buffer, int bufferSize, Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override;
  // Simplification
  Expression shallowReduce(ReductionContext reductionContext) override;
  LayoutShape leftLayoutShape() const override { return LayoutShape::MoreLetters; };
  LayoutShape rightLayoutShape() const override { return LayoutShape::BoundaryPunctuation; }
  // Evaluation
  Evaluation<float> approximate(SinglePrecision p, ApproximateContext approximateContext) const override { return templatedApproximate<float>(context, complexFormat, angleUnit); }
  Evaluation<double> approximate(DoublePrecision p, ApproximateContext approximateContext) const override { return templatedApproximate<double>(context, complexFormat, angleUnit); }
  template<typename T> Evaluation<T> templatedApproximate(Context * context, Preferences::ComplexFormat complexFormat, Preferences::AngleUnit angleUnit) const;

  // Properties
  virtual const char * functionHelperName() const = 0;
};

class MatrixEchelonForm : public Expression {
public:
  MatrixEchelonForm(const MatrixEchelonFormNode * n) : Expression(n) {}
  Expression shallowReduce(ExpressionNode::ReductionContext reductionContext);
  bool isFormReduced() const { return static_cast<MatrixEchelonFormNode *>(node())->isFormReduced(); }
};

}

#endif
