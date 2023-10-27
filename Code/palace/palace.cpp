#include "palace.hpp"

palace::palace() {
  moss().sanity_checks();
}

void palace::get_server_games() {
  southbankJson = nlohmann::json::parse(moss().get_string_data_from_server("https://adastral.net/a/southbank.json"));  // do error checking here
}


int palace::init_games() {
  std::filesystem::path smPath = "/home/rr/.steam/steam/steamapps/sourcemods";
  for(const auto& it: southbankJson["games"].items()){
    std::string version;
    if(std::filesystem::exists(smPath / it.key())) {
      std::cout << it.key() << ": Game exists. " <<std::endl;
      std::ifstream data(smPath / it.key() / ".adastral");
      if (data.fail()) {
        return 1;  // TODO: handle this properly. we also need to check the json's not invalid but uhhh idk since it's a stream
      }
      nlohmann::json filedata = nlohmann::json::parse(data);
      version = filedata["version"];
    }
      std::string full_url = southbankJson["dl_url"];
      full_url += it.key();
      full_url += '/'; // this is dumb, make it do this inside kachemak....
      auto* game = new Kachemak(smPath,it.key(),full_url,version); // getting the json is versioning impl specific so we let it get it
      // i'm aware i'm breaking one of the rules, but it makes more sense
      serverGames[it.key()] = game;
  }
  return 0;
}

int palace::update_game(const std::string& game_name) {
  serverGames[game_name]->Update();
  return 0;
}