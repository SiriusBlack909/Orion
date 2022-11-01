#include "oripch.h"
#include "Mesh.h"

namespace Orion 
{
	Mesh::Mesh(const Shared<Mesh>& mesh)
	{
		m_Material = mesh->GetMaterial();
		m_Indices.reserve(mesh->GetIndicesCount());
		m_Vertices.reserve(mesh->GetVerticesCount());


		memcpy(m_Vertices.data(), mesh->GetVerticesData(), sizeof(MeshVertex) * mesh->GetVerticesCount());
		memcpy(m_Indices.data(), mesh->GetVerticesData(), sizeof(uint32_t) * mesh->GetIndicesCount());



		SetupMesh();
	}


	void Mesh::Render(Shared<Shader>& shader)
	{
		 shader->Bind();
		 if (m_Material.diffuseMap)
		 shader->SetInt("u_Material.diffuse", m_Material.diffuseMap->GetCurrentSlot());
		 else shader->SetInt("u_Material.diffuse", 0);

		 if(m_Material.specularMap)
		 shader->SetInt("u_Material.specular", m_Material.specularMap->GetCurrentSlot());
		 else shader->SetInt("u_Material.specular", 0);

		 if(m_Material.shininess)
		 shader->SetFloat("u_Material.shininess", m_Material.shininess);
		 else  shader->SetFloat("u_Material.shininess", 0.0f);

		// RenderCommand::DrawArray(m_MeshVertexArray, m_Vertices.size());

		RenderCommand::DrawIndexed(m_MeshVertexArray, m_Indices.size());
	}

	void Mesh::SetupMesh()
	{

		m_MeshVertexArray = VertexArray::Create();
		m_MeshVertexArray->Bind();
		Shared<IndexBuffer> indexBuffer = IndexBuffer::Create(m_Indices.data(), m_Indices.size());
		m_MeshVertexArray->SetIndexBuffer(indexBuffer);


		Shared<VertexBuffer> vertexBuffer = VertexBuffer::Create((float*)m_Vertices.data(), m_Vertices.size() * sizeof(MeshVertex));
		vertexBuffer->SetLayout({
		{Orion::ShaderDataType::Float3, "a_Position"},
		{Orion::ShaderDataType::Float3, "a_Normal"},
		{Orion::ShaderDataType::Float3, "a_Tangent"},
		{Orion::ShaderDataType::Float3, "a_Bitangent"},
		{Orion::ShaderDataType::Float4, "a_Color"},
		{Orion::ShaderDataType::Float2, "a_TextureCoord"},
		{Orion::ShaderDataType::Float, "a_TextureSlot"}
			});

		m_MeshVertexArray->AddVertexBuffer(vertexBuffer);

	}

}