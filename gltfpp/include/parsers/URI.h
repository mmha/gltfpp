#pragma once
#include "../Error.h"
#include "../URI.h"
#include "Parsing.h"
#include <algorithm>

namespace gltfpp {
	inline namespace v1 {
		namespace detail {
			template <typename CharIterator>
			struct data_uri_result {
				CharIterator mime_begin, mime_end;
				CharIterator data_begin, data_end;

				constexpr bool has_mime() const {
					return mime_begin != mime_end;
				}

				constexpr bool has_data() const {
					// This should always be true
					return data_begin != data_end;
				}

				constexpr operator bool() const {
					return has_data();
				}
			};

			template <typename CharIterator>
			auto parse_data_uri(CharIterator uri_begin, CharIterator uri_end) -> data_uri_result<CharIterator> {
				using std::begin;
				using std::end;
				data_uri_result<CharIterator> result;

				constexpr char expected_prefix[] = "data:";
				const auto prefixMatch = std::mismatch(begin(expected_prefix), end(expected_prefix), uri_begin);
				if(prefixMatch.first == end(expected_prefix)) {
					return {};
				}

				// It probably is a data uri, look for ',' or ';' in the entire uri
				// Find the mime type or the begin of the data (marked with a ',')
				{
					result.mime_begin = prefixMatch.second;
					result.mime_end = std::find_if(result.mime_begin, uri_end, [](auto c) { return c == ',' || c == ';'; });
					if(result.mime_end == uri_end) {
						return {};
					}
				}
				if(*result.mime_end == ';') {
					result.data_begin = std::next(result.mime_end, 1);
					result.data_begin = std::find(result.data_begin, uri_end, ',') + 1;
					if(result.data_begin == uri_end + 1) {
						return {};
					}
				} else {
					result.data_begin = ++result.mime_end;
				}
				result.data_end = uri_end;
				return result;
			}
		}

		inline auto parse(URI &uri) {
			using namespace detail;
			return [&](ParseContext ctx) -> gltf_result<ParseContext> {
				if(!ctx.json->is_string()) {
					return make_unexpected(gltf_error::type_error);
				}
				// TODO is there a view type that does not allocate in nlohmann::json?
				const auto &str = ctx.json->get<std::string>();
				const auto parse_result = parse_data_uri(str.begin(), str.end());
				if(!parse_result) {
					return make_unexpected(gltf_error::decode_error);
				}
				// TODO something useful with the mime type
				try {
					decode_embedded_base64(parse_result.data_begin, parse_result.data_end, std::back_inserter(uri));
				} catch(...) { return make_unexpected(gltf_error::decode_error); }
				return {};
			};
		}
	}	// namespace v1
}	// namespace gltfpp
