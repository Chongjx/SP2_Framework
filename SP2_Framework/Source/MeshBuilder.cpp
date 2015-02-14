/******************************************************************************/
/*!
\file	MeshBuilder.cpp
\author Chuk Yih Jou
\brief
Build meshes and object here
*/
/******************************************************************************/
#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "Vertex.h"
#include "MyMath.h"
#include "LoadOBJ.h"

/******************************************************************************/
/*!
\brief
Generate the vertices of a OBJ; 

\param meshName - name of mesh
\param file_path - name of the file

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/

Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path) {
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;

	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);

	if(!success)
		return NULL;

	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
	//Create the mesh and call glBindBuffer, glBufferData
	//Use triangle list and remember to set index size

    Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);

	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;
	return mesh;
    
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

    v.pos.Set(0, 0, 0);
    v.color.Set(1.f, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(1.0f, 0, 0);
	v.color.Set(1.f, 0, 0);
	vertex_buffer_data.push_back(v);

    v.pos.Set(0, 0, 0);
    v.color.Set(0, 1.f, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, 0.75f, 0);
	v.color.Set(0, 1.f, 0);
	vertex_buffer_data.push_back(v);

    v.pos.Set(0, 0, 0);
    v.color.Set(0, 0, 1.f);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0, 0, 1.0f);
	v.color.Set(0, 0, 1.f);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(0); 
    index_buffer_data.push_back(1);
    index_buffer_data.push_back(2); 
	index_buffer_data.push_back(3);
    index_buffer_data.push_back(4); 
    index_buffer_data.push_back(5);
	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);

	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;
	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a text quad; 

\param meshName - name of mesh
\param numRow - width of quad
\param numCol - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol)
{
    float width = 1.0f / numCol;
	float height = 1.0f / numRow;
    Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

    int offset = 0;

	for(int i = numRow - 1; i >= 0; --i)
	{
		for(unsigned int j = 0; j < numCol; ++j)
		{
            v.pos.Set(-0.5, -0.5, 0);
            v.texCoord.Set(j * width, i * height);
            vertex_buffer_data.push_back(v);

            v.pos.Set(0.5, -0.5, 0);
            v.texCoord.Set(j * width + width, i * height);
            vertex_buffer_data.push_back(v);

            v.pos.Set(0.5, 0.5, 0); 
            v.texCoord.Set(j * width + width, i * height + height);
            vertex_buffer_data.push_back(v);

            v.pos.Set(-0.5, 0.5, 0);
            v.texCoord.Set(j * width, i * height + height);
            vertex_buffer_data.push_back(v);

            //Task: Add 6 indices into index_buffer_data
            index_buffer_data.push_back(offset + 1);
            index_buffer_data.push_back(offset + 2);
            index_buffer_data.push_back(offset + 0);
            index_buffer_data.push_back(offset + 0);
            index_buffer_data.push_back(offset + 2);
            index_buffer_data.push_back(offset + 3);

            offset += 4;
		}
	}

    Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
    
    v.pos.Set(1, 0, -1);
    v.normal.Set(0, 1, 0);
    v.texCoord.Set(0, 0);
    vertex_buffer_data.push_back(v);

    v.pos.Set(1, 0, 1);
    v.normal.Set(0, 1, 0);
    v.texCoord.Set(0, length);
    vertex_buffer_data.push_back(v);

    v.pos.Set(-1, 0, 1); 
    v.normal.Set(0, 1, 0);
    v.texCoord.Set(length, length);
    vertex_buffer_data.push_back(v);

    v.pos.Set(-1, 0, -1);
    v.normal.Set(0, 1, 0);
    v.texCoord.Set(length, 0);
    vertex_buffer_data.push_back(v);

    std::vector<GLuint> index_buffer_data;
    //Task: Add 6 indices into index_buffer_data
    index_buffer_data.push_back(1); //2
    index_buffer_data.push_back(0);//1
    index_buffer_data.push_back(2);//4
    index_buffer_data.push_back(0);//1
    index_buffer_data.push_back(3);//5
    index_buffer_data.push_back(2);
    //4
    /*
    v.pos.Set(-0.5, -0.5, 0);
    v.color = color;
    v.normal.Set(0, 1, 0);
    v.texCoord.Set(0, 0);
    vertex_buffer_data.push_back(v);

    v.pos.Set(0.5, -0.5, 0);
    v.color = color;
    v.normal.Set(0, 1, 0);
    v.texCoord.Set(0, 0);
    vertex_buffer_data.push_back(v);

    v.pos.Set(0.5, 0.5, 0); 
    v.color = color;
    v.normal.Set(0, 1, 0);
    v.texCoord.Set(0, 0);
    vertex_buffer_data.push_back(v);

    v.pos.Set(-0.5, 0.5, 0);
    v.color = color;
    v.normal.Set(0, 1, 0);
    v.texCoord.Set(0, 0);
    vertex_buffer_data.push_back(v);

    std::vector<GLuint> index_buffer_data;
    //Task: Add 6 indices into index_buffer_data
    index_buffer_data.push_back(1);
    index_buffer_data.push_back(2);
    index_buffer_data.push_back(0);
    index_buffer_data.push_back(0);
    index_buffer_data.push_back(2);
    index_buffer_data.push_back(3);*/

    /*
	v.pos.Set(0.5, 0.5, 0);
	v.color = color;
	v.normal.Set(0, 1, 0);
    v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5, -0.5, 1);
	v.color = color;
	v.normal.Set(0, 1, 0);
    v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5, 0.5, 1); 
	v.color = color;
	v.normal.Set(0, 1, 0);
    v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5, -0.5, 1);
	v.color = color;
	v.normal.Set(0, 1, 0);
    v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(1);*/
    /*
    v.pos.Set(10, 0, -10);
	v.color = color;
	v.normal.Set(0, 1, 0);
    v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(10, 0, 10);
	v.color = color;
	v.normal.Set(0, 1, 0);
    v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(10, -10, 10); 
	v.color = color;
	v.normal.Set(0, 1, 0);
    v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);
    /*
    v.pos.Set(10, 10, 10);
	v.color = color;
	v.normal.Set(0, 1, 0);
    v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(10, 0, 10);
	v.color = color;
	v.normal.Set(0, 1, 0);
    v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-10, 0,10); 
	v.color = color;
	v.normal.Set(0, 1, 0);
    v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);

    std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);*/

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}


/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ)
{
	// An array of 3 vectors which represents 3 vertices
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(-lengthX,-lengthY,-lengthZ);//back bottom left
	v.color = color;
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(lengthX,-lengthY,-lengthZ); //back bottom right
	v.color = color;
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(lengthX, lengthY,-lengthZ); //back top right
	v.color = color;
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-lengthX, lengthY,-lengthZ); //back top left
	v.color = color;
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-lengthX,-lengthY, lengthZ);// front bottom left
	v.color = color;
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(lengthX,-lengthY, lengthZ); //front bottom right
	v.color = color;
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(lengthX, lengthY, lengthZ); //front top right
	v.color = color;
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-lengthX, lengthY, lengthZ); //front top left
	v.color = color;
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
    
	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(7); //front
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(5); //front
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(6); //right
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1); //right
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(3); //top
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(6); //top
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(2); //back
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0); //back
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3); //left
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(4); //left
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1); //bottom
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(4); //bottom
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);

	// Set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);

	// Transfer vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}