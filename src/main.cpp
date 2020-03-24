#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include <boost/process.hpp>

#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>

#include <fmt/format.h>
#include <pugixml.hpp>

using namespace curlpp::options;
namespace fs = std::filesystem;

const std::string BING = "https://www.bing.com";
const std::string PYWAL = "/home/asad/.local/bin/wal";
const std::string WALLPAPERS = "BingWallpaper";

typedef struct {
  std::string url;
  std::string name;
  std::string startdate;
} BingImage;

auto market() -> std::string { return std::string("en-US"); }

auto bing_xml_url() -> std::string {
  return fmt::format("{}/HPImageArchive.aspx?format=xml&idx=0&n=1&mkt={}", BING,
                     market());
}

auto bing_xml() -> std::string {
  try {
    curlpp::Cleanup cleaner;
    curlpp::Easy request;

    request.setOpt<curlpp::options::Url>(bing_xml_url());

    std::ostringstream os;
    os << request;
    return os.str();
  } catch (curlpp::RuntimeError &e) {
    std::cout << e.what() << std::endl;
    return std::string("");
  } catch (curlpp::LogicError &e) {
    std::cout << e.what() << std::endl;
    return std::string("");
  }
}

auto bing_image_info() -> BingImage {
  pugi::xml_document doc;
  auto result = doc.load_string(bing_xml().c_str());
  if (!result)
    return BingImage{"", "", ""};

  auto partial_url = std::string(
      doc.child("images").child("image").child("url").child_value());
  auto url = fmt::format("{}{}", BING, partial_url);
  auto name = partial_url.substr(11, partial_url.find(".jpg") - 11 + 4);
  auto startdate = std::string(
      doc.child("images").child("image").child("startdate").child_value());

  return BingImage{url, name, startdate};
}

auto save_bing_image() -> std::string {
  auto image = bing_image_info();
  auto fname = fmt::format("{}-{}", image.startdate, image.name);
  auto filename =
      fs::path("/home/asad/Pictures") / fs::path(WALLPAPERS) / fs::path(fname);

  try {
    curlpp::Cleanup cleaner;
    curlpp::Easy request;

    std::ofstream output;
    output.open(filename.string());

    std::cout << "will be located under: " << filename << std::endl;

    request.setOpt<curlpp::options::WriteStream>(&output);
    request.setOpt<curlpp::options::Url>(image.url);
    request.perform();

    output.close();

    return filename.string();
  } catch (curlpp::LogicError &e) {
    std::cout << e.what() << std::endl;
  } catch (curlpp::RuntimeError &e) {
    std::cout << e.what() << std::endl;
  }

  return "";
}

void run() {
  auto image = save_bing_image();
  if (image == "") {
    std::cout << "There's no file to apply" << std::endl;
    return;
  } else {
    boost::process::child(fmt::format("{} {} {}", PYWAL, "-i", image)).wait();
  }
}

int main(int, char **) {
  run();
  return 0;
}
