#pragma once
#include <exception>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>

namespace bwa {
	namespace detail {
		/*
			Checks if an object has a loadFromFile function
			Almost all SFML resources have this function
		*/
		template <typename T, typename Enable = std::void_t<>>
		struct has_loadFromFile_function
			: std::false_type {};

		template <typename T>
		struct has_loadFromFile_function<T,
			std::void_t<decltype(std::declval<T>().loadFromFile(""))>>
			: std::true_type {};

		/*
			Checks if an object has a openFromFile function
			For example sf::Music
		*/
		template <typename T, typename Enable = std::void_t<>>
		struct has_openFromFile_function
			: std::false_type {};

		template <typename T>
		struct has_openFromFile_function<T,
			std::void_t<decltype(std::declval<T>().openFromFile(""))>>
			: std::true_type {};

		/*
			The implementation of the ResourceLoader service class.
			Resources are stored in maps by their unique type
			so loading an sf::Texture and an sf::Font would yield
			two maps. This is so that if you try to retrieve a resource
			with the wrong type you get a runtime error for
			accessing a key that doesn't exist.
		*/
		template <typename T, typename Enable = std::void_t<>>
		struct ResourceLoader_impl {};

		/*
			Overload for SFML objects that export a
			loadFromFile function
		*/
		template <typename T>
		struct ResourceLoader_impl<T, 
			std::enable_if_t<has_loadFromFile_function<T>::value>> {
		protected:
			static std::shared_ptr<T> load(const std::string& filename) {
				auto ptr = std::make_shared<T>();
				if (!ptr->loadFromFile(filename))
					throw std::runtime_error("Failed to load '" + filename + "' as '" + typeid(T).name() + "'");
				return std::move(ptr);
			}
		};

		/*
			Overload for SFML objects that export a
			openFromFile function (sf::Music)
		*/
		template <typename T>
		struct ResourceLoader_impl<T,
			std::enable_if_t<has_openFromFile_function<T>::value>> {
		protected:
			static std::shared_ptr<T> load(const std::string& filename) {
				auto ptr = std::make_shared<T>();
				if (!ptr->openFromFile(filename))
					throw std::runtime_error("Failed to load '" + filename + "' as '" + typeid(T).name() + "'");
				return std::move(ptr);
			}
		};
	}

	/*
		The interface to load or get a resource.
		It should be used like so:

		auto tex = bwa::ResourceLoader<sf::Texture>::get("some_image.png");
		
		'tex' would be of the type 'std::shared_ptr<sf::Texture>'
	*/
	template <typename T>
	struct ResourceLoader final : detail::ResourceLoader_impl<T> {
		static std::shared_ptr<T> get(const std::string& filename) {
			if (_map.count(filename))
				return _map.at(filename);
			else
				return load(filename);
		}

	private:
		/*
			ResourceLoader checks this map with the specific
			type you used to instantiate it for a string equal to
			the filename. If it finds it will return a resource.
			If not it will try to load it. If any errors come up
			a 'std::runtime_error' will be thrown.
		*/
		static std::map<std::string, std::shared_ptr<T>> _map;
	};

	/*
		Declares the _map in ResourceLoader
		by calling its default ctor.
	*/
	template <typename T>
	std::map<std::string, std::shared_ptr<T>> ResourceLoader<T>::_map;
}
