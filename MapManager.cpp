#include "MapManager.hpp"

#include <memory>

namespace MapManager{


    inline std::string toBinary(int t){
        return std::string((char*)&t, sizeof(t));
    }
    inline std::string toBinary(bool t){
        return std::string((char*)&t, 1);
    }

    int save(std::vector< std::vector<bool> > tileMap, int pixelsPerSquare, std::vector<Vec2i> pathPoints, std::string fileName){
        std::ofstream file(fileName, std::ios::trunc|std::ios::binary);
        if(!file.is_open())
            return 1;
        if(tileMap.size()<=0)
            return 2;
        int n = tileMap[0].size();
        if(n<=0)
            return 3;
        for(int i=1; i<tileMap.size(); i++)
            if(tileMap[i].size()!=n)
                return 3;
        if(pixelsPerSquare<1)
            return 4;
        if(pathPoints.size()<2)
            return 5;

        file << toBinary((int) tileMap.size()) << toBinary((int) tileMap[0].size()) << toBinary((int) pathPoints.size()) << toBinary(pixelsPerSquare);
        for(int i=0; i<tileMap.size(); i++)
            for(int j=0; j<tileMap[i].size(); j++)
                file << toBinary((bool)tileMap[i][j]);
        for(auto it = pathPoints.begin(); it != pathPoints.end(); it++)
            file << toBinary(it->x) << toBinary(it->y);

        return 0;
    }

    int load(std::vector< std::vector<bool> >& tileMap, int& pixelsPerSquare, std::vector<Vec2i>& pathPoints, std::string fileName){
        std::ifstream file(fileName, std::ios::ate);
        if(!file.is_open())
            return 1;

        int size = file.tellg();
        if(size<sizeof(int)*8+1)
            return 2;

        file.seekg(0);
        tileMap.clear();
        pathPoints.clear();

        unsigned int x,y,n;
        std::unique_ptr<char[]> buffPtr = std::make_unique<char[]>(sizeof(int)*4);
        char* buff = buffPtr.get();

        file.read(buff, sizeof(int)*4);
        x = *(int*)buff;
        y = *(int*)(buff+sizeof(int));
        n = *(int*)(buff+sizeof(int)*2);
        pixelsPerSquare = *(int*)(buff+sizeof(int)*3);
        for(int i=0; i<x; i++)
            tileMap.push_back(std::vector<bool>(y, true));
            
        buffPtr = std::make_unique<char[]>(x*y);
        buff = buffPtr.get();
        file.read(buff, x*y);
        for(int i=0; i<x; i++)
            for(int j=0; j<y; j++)
                if(buff[i*y + j]==0)
                    tileMap[i][j] = false;
                    
        buffPtr = std::make_unique<char[]>(sizeof(int)*n*2);
        buff = buffPtr.get();
        file.read(buff, sizeof(int)*n*2);
        pathPoints.resize(n);
        for(int i=0; i<n; i++){
            pathPoints[i].x = *(int*)(buff+i*sizeof(int)*2);
            pathPoints[i].y = *(int*)(buff+i*sizeof(int)*2+sizeof(int));
        }

        return 0;
    }
}
