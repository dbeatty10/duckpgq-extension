//===----------------------------------------------------------------------===//
//                         DuckPGQ
//
// duckpgq/functions/function_data/local_clustering_coefficient_function_data.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once
#include "duckdb/main/client_context.hpp"

namespace duckdb {
struct LocalClusteringCoefficientFunctionData : FunctionData {
  ClientContext &context;
  int32_t csr_id;

  LocalClusteringCoefficientFunctionData(ClientContext &context, int32_t csr_id);
  static unique_ptr<FunctionData>
  LocalClusteringCoefficientBind(ClientContext &context, ScalarFunction &bound_function,
                      vector<unique_ptr<Expression>> &arguments);

  unique_ptr<FunctionData> Copy() const override;
  bool Equals(const FunctionData &other_p) const override;
};

} // namespace duckdb