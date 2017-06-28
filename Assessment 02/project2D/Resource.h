#pragma once

template<class T>
class Resource
{

public:
	// Constructor
		// Obtain Texture/Image (Image)
		Resource(const std::string& filename) :m_filename(filename) { m_data = std::unique_ptr<T>(new T(filename.c_str())); };
		// Obtain Fonts (Font, Size)
		Resource(const std::string& filename, int size) :m_filename(filename) { m_data = std::unique_ptr<T>(new T(filename.c_str(), size)); };

	// De-Constructor
	~Resource() {};
	std::string getFilename() { return m_filename; }

	T* get();

private:
	std::unique_ptr<T> m_data;
	std::string m_filename;
};

template<class T>
inline T * Resource<T>::get()
{
	return m_data.get();
}
