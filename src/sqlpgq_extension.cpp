#define DUCKDB_EXTENSION_MAIN

#include "sqlpgq_extension.hpp"
#include "duckdb.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/common/string_util.hpp"
#include "duckdb/function/scalar_function.hpp"


#include <duckdb/parser/parsed_data/create_scalar_function_info.hpp>

namespace duckdb {

inline void SqlpgqScalarFun(DataChunk &args, ExpressionState &state, Vector &result) {
    auto &name_vector = args.data[0];
    UnaryExecutor::Execute<string_t, string_t>(
	    name_vector, result, args.size(),
	    [&](string_t name) { 
			return StringVector::AddString(result, "Sqlpgq "+name.GetString()+" 🐥");;
        });
}

static void LoadInternal(DatabaseInstance &instance) {
	Connection con(instance);
    con.BeginTransaction();

    auto &catalog = Catalog::GetSystemCatalog(*con.context);

    CreateScalarFunctionInfo sqlpgq_fun_info(
            ScalarFunction("sqlpgq", {LogicalType::VARCHAR}, LogicalType::VARCHAR, SqlpgqScalarFun));
    sqlpgq_fun_info.on_conflict = OnCreateConflict::ALTER_ON_CONFLICT;
    catalog.CreateFunction(*con.context, &sqlpgq_fun_info);
    con.Commit();
}

void SqlpgqExtension::Load(DuckDB &db) {
	LoadInternal(*db.instance);
}
std::string SqlpgqExtension::Name() {
	return "sqlpgq";
}

} // namespace duckdb

extern "C" {

DUCKDB_EXTENSION_API void sqlpgq_init(duckdb::DatabaseInstance &db) {
	LoadInternal(db);
}

DUCKDB_EXTENSION_API const char *sqlpgq_version() {
	return duckdb::DuckDB::LibraryVersion();
}
}

#ifndef DUCKDB_EXTENSION_MAIN
#error DUCKDB_EXTENSION_MAIN not defined
#endif
