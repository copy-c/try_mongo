#include <chrono>
#include <vector>

#include "absl/strings/str_join.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "nlohmann/json.hpp"
#include "fmt/format.h"

#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/builder/list.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

using nlohmann::json;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

int main(int, char**) {
    std::vector<std::string> v = {"foo","bar","baz"};
    std::string s = absl::StrJoin(v, "-");
    std::cout << fmt::format("{}=", s);

    json test = 1;

    try {
        // The mongocxx::instance constructor and destructor initialize and shut down the driver,
        // respectively. Therefore, a mongocxx::instance must be created before using the driver and
        // must remain alive for as long as the driver is in use.
        const auto uri = mongocxx::uri{
                "mongodb+srv://copy:muqurenxuexi@cluster0.s5iqjku.mongodb.net/?retryWrites=true&w=majority"};
            // Set the version of the Stable API on the client.
        mongocxx::options::client client_options;
        const auto api = mongocxx::options::server_api{mongocxx::options::server_api::version::k_version_1};
        client_options.server_api_opts(api);
        // Setup the connection and get a handle on the "admin" database.
        mongocxx::client client{uri, client_options};
        mongocxx::database db = client["scheduler"];  // If the database you request does not exist, MongoDB creates it when you first store data.
        auto sch_db = db["appointments"];  // If the database you request does not exist, MongoDB creates it when you first store data.

        // insert
        json event = R"({"start": "1"})"_json;
        auto doc_event = bsoncxx::from_json(event.dump());
        auto res = sch_db.insert_one(std::move(doc_event));
        auto id  = res->inserted_id();
        // bsoncxx::to_json(res->inserted_id());
        // std::cout << id.get() << std::endl;

        // minsert
        json event1 = R"({"start": "2"})"_json;
        auto doc_event1 = bsoncxx::from_json(event1.dump());
        json event2 = R"({"start": "3"})"_json;
        auto doc_event2 = bsoncxx::from_json(event2.dump());
        auto res_m = sch_db.insert_many(std::vector<bsoncxx::document::value>{doc_event1, doc_event2});
        auto res_m_view = res_m->result();
        auto res_m_ids = res_m->inserted_ids();

        // get
        auto find_one = sch_db.find_one(make_document(kvp("_id", id)));
        std::cout << bsoncxx::to_json(find_one->view()) << std::endl;

        // list
        auto cursor_all = sch_db.find({});
        for (auto doc : cursor_all) {
            std::cout << bsoncxx::to_json(doc, bsoncxx::ExtendedJsonMode::k_relaxed) << std::endl;
        }

        std::cout << "Pinged your deployment. You successfully connected to MongoDB!" << std::endl;
    } catch (const std::exception& e)
    {
        // Handle errors
        std::cout<< "Exception: " << e.what() << std::endl;
    }


    // TODO: fix dates


    int i = 0;
    // We choose to move in our document here, which transfers ownership to insert_one()
    // auto res = db["restaurants"].insert_one(std::move(bson));
}