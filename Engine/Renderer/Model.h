//
// Created by pedro-souza on 20/04/2026.
//
#include <string>
#include <vector>

class Model {
public:
    Model();
    ~Model() = default;

    bool LoadFromJson(const std::string &fileName, class Renderer* renderer);

    class Texture* GetTexture(size_t textureIndex) const;
    class Mesh* GetMesh() const { return mMesh; }

private:
    Mesh* mMesh;
    std::vector<Texture*> mTextures;
};
