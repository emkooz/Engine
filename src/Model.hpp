#ifndef MODEL_LOADER
#define MODEL_LOADER

class ModelLoader
{
	private:
	
	public:
	bool ObjVert (const char * path, std::vector<glm::vec3> & vert); // loads a .obj with ONLY verts
	bool ObjUV (const char * path, std::vector<glm::vec3> & vert, std::vector<glm::vec2> & uv); // loads a .obj with verts and UV's 
	bool ObjNormal (const char * path, std::vector<glm::vec3> & vert , std::vector<glm::vec2> & uv , std::vector<glm::vec3> & normal); // loads a .obj with verts, uv's, and normals
};

#endif
