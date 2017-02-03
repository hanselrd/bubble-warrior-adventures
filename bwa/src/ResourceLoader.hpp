#pragma once
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

/*
	ResourceLoader utility class.
	Currently only supports SFML objects.

	Example usage:
		auto texture = bwa::ResourceLoader<sf::Texture>::get("my_image.png");
		sf::Sprite sprite;
		sprite.setTexture(*texture);

	You can also preload resources into the cache and get them later:
		bool success = bwa::ResourceLoader<sf::Texture>::load("my_image.png");
*/

namespace bwa {
	template <typename T>
	class ResourceLoader final {
	private:
		/*
			Private internal helper that
			lets you store a resource under 'key'
			in the _cache. If it already exists
			it will be overwritten.
		*/
		template <typename F, typename... Args>
		static bool loadHelper(const std::string& key, F&& f, Args&&... args) {
			auto ptr = std::make_shared<T>();

			/*
				Calls 'f' using the arguments, if any, in 'Args' and
				stores whether it was successful or not in the variable
				success. This also ensures that 'f' must return a bool
				or a type convertible to one.
			*/
			bool success = std::forward<F>(f)(ptr.get(), std::forward<Args>(args)...);
			
			/*
				If call to 'f' was successfull, store the loaded
				resource in _cache.
			*/
			if (success)
				_cache.insert(std::make_pair(key, ptr));

			return success;
		}

	public:
		/*
			Overload for SFML objects that export a
			loadFromFile function ex: (sf::Texture)
		*/
		template <typename U = T>
		static auto load(const std::string& filename) -> decltype(std::declval<U>().loadFromFile("")) {
			return loadHelper(filename, [](U* ptr, const std::string& filename) {
				return ptr->loadFromFile(filename);
			}, filename);
		}

		/*
			Overload for SFML objects that export a
			openFromFile function ex: (sf::Music)
		*/
		template <typename U = T, int = 0>
		static auto load(const std::string& filename) -> decltype(std::declval<U>().openFromFile("")) {
			return loadHelper(filename, [](U* ptr, const std::string& filename) {
				return ptr->openFromFile(filename);
			}, filename);
		}

		/*
			Unlike the load functions, which only loads
			the resource and doesn't return it, this function
			returns a pointer to your resource and it
			can be shared throughout the game. If the resource
			exists it'll fetch it from the cache. If not it'll
			load it first and then return it to you.
		*/
		static std::shared_ptr<T> get(const std::string& filename) {
			/*
				Checks if 'filename' hasn't been loaded,
				if it hasn't then it calls the load function
				which will go to the correct overload depending
				on type T.
			*/
			if (!_cache.count(filename))
				/*
					Checks if load was successful, if not,
					throws 'std::runtime_error'
				*/
				if (!load(filename))
					throw std::runtime_error("Could not load: " + filename);
			
			/*
				Returns the resource from the cache
			*/
			return _cache.at(filename);
		}

	private:
		/*
			ResourceLoader checks this map with the specific
			type you used to instantiate it for a string equal to
			the filename. If it finds it, it will return a resource.
		*/
		static std::map<std::string, std::shared_ptr<T>> _cache;
	};

	/*
		Instantiates the static _cache in ResourceLoader
		by calling its default ctor.
	*/
	template <typename T>
	std::map<std::string, std::shared_ptr<T>> ResourceLoader<T>::_cache;
}