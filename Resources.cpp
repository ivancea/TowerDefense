#include "Resources.hpp"

namespace Resources{

    std::map<std::string, sf::Texture*> _textures;

    void normalizePath(std::string& path){
        for(char& c:path)
            if(c=='\\')
                c = '/';
        size_t pos;
        while((pos=path.find("//")) != std::string::npos)
            path.erase(pos, 1);
        while((pos=path.find("/./")) != std::string::npos)
            path.erase(pos,2);
        while((pos=path.find("/../")) != std::string::npos)
            path.erase(pos,3);
        while(path.substr(0, 2) == "./")
            path.erase(pos,2);
        while(path.substr(0, 1) == "/")
            path.erase(pos,1);
    }

    sf::Texture* getTexture(std::string path){
        normalizePath(path);
        auto it = _textures.find(path);
        if(it!=_textures.end())
            return it->second;

        sf::Texture* tex = new sf::Texture();
        if(tex->loadFromFile("resources/" + path)){
            _textures[path] = tex;
            return tex;
        }
        delete tex;
        return nullptr;
    }
}
