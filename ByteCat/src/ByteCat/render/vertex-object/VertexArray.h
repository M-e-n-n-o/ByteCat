#pragma once

#include <vector>
#include <memory>
#include "byteCat/render/vertex-object/Buffer.h"

namespace BC
{
	/*
	 * Class VertexArray:
	 *		This class represents a 3D/2D model, without transformation.
	 *		This class is also called VAO.
	 */
	class VertexArray
	{
	private:
		unsigned int id;
		unsigned int vboIndex = 0;
		
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;
	public:
		VertexArray();
		~VertexArray();

		// Call this function to bind the VAO
		void bind() const;
		// Call this function to unbind the VAO
		void unbind() const;

		// Call this function to add a VBO (a list with data about the model) to the VAO
		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer);
		// Call this function to set the index buffer of the VAO
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer);

		const unsigned int getId() const { return id; }
		const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const { return vertexBuffers; }
		const std::shared_ptr<IndexBuffer>& getIndexBuffer() const { return indexBuffer; }

		static std::shared_ptr<VertexArray> Create()
		{
			return std::make_shared<VertexArray>();
		}
	};
}
