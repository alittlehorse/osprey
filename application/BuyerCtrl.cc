#include "BuyerCtrl.h"
//add definition of your processing function here
void drogon::BuyerCtrl::compute_query(application::Buyer &&buyer,
                                      std::function<void(const HttpResponsePtr &)> &&callback) const {

    Json::Value ret;
    ret["result"]="ok";
    ret["message"]="I received your query";
    ret["program"]=buyer.program;
    ret["verify_program"]=buyer.verify_program;
    auto resp=HttpResponse::newHttpJsonResponse(ret);
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    callback(resp);
}

void
drogon::BuyerCtrl::hello(const drogon::HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
const
{
    auto resp=HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_HTML);
    resp->setBody("hello world!");
    callback(resp);

}
