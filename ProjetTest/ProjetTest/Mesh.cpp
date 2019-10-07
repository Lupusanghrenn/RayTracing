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
	/*string[] lines = System.IO.File.ReadAllLines(@"Assets/buddha.off");
		Debug.Log(lines[0]);
	string[] tmp = lines[1].Split(' ');
	int nbVertex = int.Parse(tmp[0]);
	int nbTriangles = int.Parse(tmp[1]);

	List<Vector3> vertices = new List<Vector3>();
	List<Vector3> normales = new List<Vector3>();
	List<Vector3> normalesVertices = new List<Vector3>();
	List<int> triangles = new List<int>();
	MeshFilter mshFilter = gameObject.AddComponent<MeshFilter>();
	MeshRenderer mshRenderer = gameObject.AddComponent<MeshRenderer>();
	Vector3 sommeSommets = new Vector3();//centrage
	float biggestNorme = 0;//normalisation

	for (int i = 0; i < nbVertex; i++)
	{
		string[] tmpVertex = lines[i + 2].Split(' ');
		float x = float.Parse(tmpVertex[0], CultureInfo.InvariantCulture);
		float y = float.Parse(tmpVertex[1], CultureInfo.InvariantCulture);
		float z = float.Parse(tmpVertex[2], CultureInfo.InvariantCulture);
		var vecTmp = new Vector3(x, y, z);
		vertices.Add(vecTmp);
		sommeSommets += vecTmp;
		if (vecTmp.magnitude > biggestNorme)
		{
			biggestNorme = vecTmp.magnitude;
		}
	}

	int test = 0;
	for (int i = 2 + nbVertex; i < (2 + nbVertex + nbTriangles); i++)
	{
		string[] tmpVertex = lines[i].Split(' ');
		int s1 = int.Parse(tmpVertex[1], CultureInfo.InvariantCulture);
		int s2 = int.Parse(tmpVertex[2], CultureInfo.InvariantCulture);
		int s3 = int.Parse(tmpVertex[3], CultureInfo.InvariantCulture);
		triangles.Add(s1);
		triangles.Add(s2);
		triangles.Add(s3);

		//calcul des normales
		Vector3 lhs = vertices[s2] - vertices[s1];
		Vector3 rhs = vertices[s3] - vertices[s2];
		normales.Add(Vector3.Cross(lhs, rhs));
		test = i;
	}
	Debug.Log(triangles.Count);


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
