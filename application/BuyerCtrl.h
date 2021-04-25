#pragma once
#include <drogon/HttpController.h>
namespace application{
    struct Buyer{
        std::size_t register_count;
        std::size_t  word_size;
        std::size_t tinyram_input_size_bound;
        std::size_t time_bound;
        std::string program;
        std::string verify_program;
    };
}
namespace drogon
{
template<>
inline application::Buyer fromRequest(const HttpRequest &req) {
    auto json = req.getJsonObject();
    application::Buyer buyer;
    if (json) {
        buyer.register_count = (*json)["register_count"].asUInt64();
        buyer.word_size = (*json)["word_size"].asUInt64();
        buyer.tinyram_input_size_bound = (*json)["tinyram_input_size_bound"].asUInt64();
        buyer.time_bound = (*json)["time_bound"].asUInt64();
        buyer.program = (*json)["program"].asString();
        buyer.verify_program = (*json)["verify_program"].asString();
    }
    return buyer;
}

class BuyerCtrl : public drogon::HttpController<BuyerCtrl> {
public:
    METHOD_LIST_BEGIN
        //use METHOD_ADD to add your custom processing function here;
        ADD_METHOD_TO(BuyerCtrl::compute_query, "/compute_query", Post);
        ADD_METHOD_TO(BuyerCtrl::hello, "/", {Get,Post});

    METHOD_LIST_END

    // your declaration of processing function maybe like this:
    void compute_query(application::Buyer &&buyer, std::function<void(const HttpResponsePtr &)> &&callback) const;
    void hello(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback) const;

};

}