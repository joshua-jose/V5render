class Mesh
{
private:

	Subset **Subsets;
public:
	static Mesh* FromFile(string path);
	int32 SubsetCount;

	Mesh(int32 subsetCount);
	~Mesh();

	int32 getSubsetCount();
	int32 getVertexCount();
	int32 getTriangleCount();
	Subset* getSubset(int32 index);

	void Draw(Matrix modelSpace);
	void TransformVertices(Matrix matrix);
};
