// Copyright [2021] <Copyright syheliel>
#include "BuyerCtrl.h"

#include <libserver/osprey_server.hpp>

void drogon::BuyerCtrl::compute_query(
    application::Requester &&requester,
    std::function<void(const HttpResponsePtr &)> &&callback) const {
  Json::Value ret;
  ret["result"] = "ok";
  ret["message"] = "I received your query";
  ret["program"] = requester.program;
  ret["verify_program"] = requester.verify_program;
  auto resp = HttpResponse::newHttpJsonResponse(ret);
  resp->setStatusCode(k200OK);
  resp->setContentTypeCode(CT_APPLICATION_JSON);
  server_provider provider;
  callback(resp);
}

void drogon::BuyerCtrl::hello(
    const drogon::HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) const {
  auto resp = HttpResponse::newHttpResponse();
  resp->setStatusCode(k200OK);
  resp->setContentTypeCode(CT_TEXT_HTML);
  resp->setBody("hello world!");
  callback(resp);
}
