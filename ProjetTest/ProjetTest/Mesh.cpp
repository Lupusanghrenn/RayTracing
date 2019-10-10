#include "Mesh.h"

Mesh::Mesh()
{
	position = Vec3<float>{ 0.f, 0.f, 0.f };
	this->color = Couleur();
	this->albedo = Albedo();
}

Mesh::Mesh(string chemin)
{
	//récupération du code avec Unity
	//TODO
	//string[] lines;
	ifstream file;
	file.open("buddha.off");
	int nbVertex, nbTriangles;
	file >> nbVertex >> nbTriangles;

	Vec3<float> sommeSommets;
	float biggestNorme = 0;
	for (int i = 0; i < nbVertex; i++)
	{
		float x, y, z;
		file >> x >> y >> z;
		Vec3<float> vecTmp = Vec3<float>{ x,y,z };
		vertices.push_back(vecTmp);
		sommeSommets = sommeSommets + vecTmp;
		if (norm(vecTmp) > biggestNorme)
		{
			biggestNorme = norm(vecTmp);
		}
	}

	for (int i = 2 + nbVertex; i < (2 + nbVertex + nbTriangles); i++)
	{
		/*string[] tmpVertex = lines[i].Split(' ');
		int s1 = int.Parse(tmpVertex[1], CultureInfo.InvariantCulture);
		int s2 = int.Parse(tmpVertex[2], CultureInfo.InvariantCulture);
		int s3 = int.Parse(tmpVertex[3], CultureInfo.InvariantCulture);*/
		int s0, s1, s2, s3;
		file >> s0 >> s1 >> s2 >> s3;
		triangles.push_back(s1);
		triangles.push_back(s2);
		triangles.push_back(s3);

		//calcul des normales
		Vec3<float> lhs = vertices[s2] - vertices[s1];
		Vec3<float> rhs = vertices[s3] - vertices[s2];
		normales.push_back(cross(lhs, rhs));
	}

	//chargement standard du maillage sans normalisation et centrage

	/*
	Vector3 centreMaillage = sommeSommets / nbVertex;
	centreMaillage = centreMaillage - new Vector3(0f, 0f, 0f);//on a donc un vecteur qui ramene le centre a O --> on applique ce vecteur a tout les points
	for (int i = 0; i < nbVertex; i++)
	{
		vertices[i] -= centreMaillage;//centrage
		vertices[i] /= biggestNorme;//normalisation
	}

	//calcul des normales par sommets
	for (int i = 0; i < nbVertex; i++)
	{
		Vector3 somNormal = new Vector3();
		int nbTrianglesHit = 0;
		//parcours des triangles
		for (int j = 0; j < triangles.Count; j += 3)
		{
			if (triangles[j] == i || triangles[j + 1] == i || triangles[j + 2] == i)
			{
				//on calcule et ajoute la normale
				Vector3 lhs = vertices[triangles[j]] - vertices[triangles[j + 1]];
				Vector3 rhs = vertices[triangles[j + 1]] - vertices[triangles[j + 2]];
				somNormal += Vector3.Cross(lhs, rhs);
				nbTrianglesHit++;
			}
		}
		//ajout de la normale
		normalesVertices.Add(somNormal / nbTrianglesHit);
	}

	Mesh msh = new Mesh();
	msh.vertices = vertices.ToArray();
	msh.triangles = triangles.ToArray();
	msh.RecalculateNormals();
	//msh.normals = normalesVertices.ToArray();

	Debug.Log(vertices.Count);

	mshFilter.mesh = msh;
	mshRenderer.material = mat;*/
}

Intersect Mesh::intersect(Rayon R)
{
	//TODO
	return Intersect();
}

Vec3<float> Mesh::getNormal(Vec3<float> point)
{
	return Vec3<float>();
}

//private void exportMaillage(List<Vector3> vertices, List<int> triangles, List<Vector3> normales, string nomFichierOut)
//{
//	System.IO.StreamWriter streamWriter = new System.IO.StreamWriter("Assets/" + nomFichierOut);
//	streamWriter.WriteLine("OFF");
//	streamWriter.WriteLine(vertices.Count + " " + triangles.Count / 3 + " 0");
//	Debug.Log(triangles[triangles.Count - 4]);
//	foreach(Vector3 vertex in vertices)
//	{
//		string line = vertex.x.ToString("0.0000000") + " " + vertex.y.ToString("0.0000000") + " " + vertex.z.ToString("0.0000000");
//		line = line.Replace(",", ".");
//		streamWriter.WriteLine(line);
//	}
//
//	for (int i = 0; i < triangles.Count; i += 3)
//	{
//
//		streamWriter.WriteLine("3 " + triangles[i] + " " + triangles[i + 1] + " " + triangles[i + 2]);
//	}
//
//	streamWriter.Close();
//}
