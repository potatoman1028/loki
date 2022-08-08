namespace loki
{
	template<typename T>
	struct object;

	template<typename T>
	class object_container;

	template<typename T>
	struct object
	{
		T* memory = nullptr;

	public:
		object();
		~object();
	};

	template<typename T>
	class object_container
	{
		size_t size = 0;
		object<T>** block = nullptr;

	public:
		object_container();
		object_container(size_t size);
		~object_container();
		void reserve(size_t size);
		void realloc();
		void realloc(size_t size);
		object<T>* at(unsigned int pos);
		void swap(unsigned int src, unsigned int dst);
		bool remove(unsigned int pos);
	};

	template<typename T>
	object<T>::object()
	{
		memory = new T();
	}

	template<typename T>
	object<T>::~object()
	{
		delete memory;
	}

	template<typename T>
	object_container<T>::object_container()
	{
	}

	template<typename T>
	object_container<T>::object_container(size_t size)
	{
		this->size = size;

		block = new object<T>*[size];

		for (int i = 0; i < size; ++i)
		{
			block[i] = new object<T>();
		}
	}

	template<typename T>
	object_container<T>::~object_container()
	{
		for (int i = 0; i < size; ++i)
		{
			if (block[i] != nullptr)
			{
				delete block[i];
			}
		}

		if (block != nullptr)
		{
			delete[] block;
		}
	}

	template<typename T>
	void object_container<T>::reserve(size_t size)
	{
		this->size = size;

		block = new object<T>*[size];

		for (int i = 0; i < size; ++i)
		{
			block[i] = new object<T>();
		}
	}

	template<typename T>
	void object_container<T>::realloc()
	{
		size_t new_size = this->size * 2;
		object<T>** new_block = new object<T>*[new_size];
		memcpy_s(new_block, sizeof(object<T>*) * new_size, this->block, sizeof(object<T>*) * this->size);

		for (size_t i = this->size; i < new_size; ++i)
		{
			new_block[i] = new object<T>();
		}

		this->size = new_size;
		delete[] block;
		block = new_block;
	}

	template<typename T>
	void object_container<T>::realloc(size_t size)
	{
		size_t new_size = this->size + size;
		object<T>** new_block = new object<T>*[new_size];
		memcpy_s(new_block, sizeof(object<T>*) * new_size, this->block, sizeof(object<T>*) * this->size);

		for (size_t i = this->size; i < new_size; ++i)
		{
			new_block[i] = new object<T>();
		}

		this->size = new_size;
		delete[] block;
		block = new_block;
	}

	template<typename T>
	object<T>* object_container<T>::at(unsigned int pos)
	{
		return block[pos];
	}

	template<typename T>
	void object_container<T>::swap(unsigned int p1, unsigned int p2)
	{
		object<T>* tmp = block[p1];
		block[p1] = block[p2];
		block[p2] = tmp;
	}

	template<typename T>
	bool object_container<T>::remove(unsigned int pos)
	{
		delete block[pos];
		block[pos] = new object<T>();
	}
}