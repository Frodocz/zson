#include <stdexcept>
#include "include/scanner.h"

namespace zson {

void Scanner::scanTrue() {
    if (m_source.compare(m_curIdx, 3, "rue") == 0) {
        m_curIdx += 3;
    } else {
        throw std::logic_error("Scan 'true' failed");
    }
}

void Scanner::scanFalse() {
    if (m_source.compare(m_curIdx, 4, "alse") == 0) {
        m_curIdx += 4;
    } else {
        throw std::logic_error("Scan 'false' failed");
    }
}

void Scanner::scanNull() {
    if (m_source.compare(m_curIdx, 3, "ull") == 0) {
        m_curIdx += 3;
    } else {
        throw std::logic_error("Scan 'null' failed");
    }
}

void Scanner::scanString() {
    size_t pos = m_curIdx;
    while (peek() != '\"' && !isAtEnd()) {
        advance();
        if (peek() == '\\') {
            advance();
            switch (peek()) {
                case 'b':
                case 't':
                case 'n':
                case 'f':
                case 'r':
                case '\"':
                case '\\':
                    advance();
                    break;
                case 'u':
                    for (int i = 0; i < 4; ++i) {
                        advance();
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (isAtEnd()) {
        throw std::logic_error("Invalid string: missing closing quote!");
    }

    advance();
    m_val_string = m_source.substr(pos, m_curIdx - pos - 1);
}

void Scanner::scanNumber() {
    size_t pos = m_curIdx - 1;
    while (isdigit(peek())) {
        advance();
    }

    if (peek() == '.' && isdigit(peekNext())) {
        advance();
        while (isdigit(peek())) {
            advance();
        }
    }

    m_val_number = std::atof(m_source.substr(pos, m_curIdx - pos).c_str());
}

Scanner::JsonTokenType Scanner::scan() {
    if (isAtEnd()) {
        return JsonTokenType::END_OF_SOURCE;
    }

    m_prevIdx = m_curIdx;
    char c = advance();
    switch (c) {
        case '{':
            return JsonTokenType::BEGIN_OBJECT;
        case '}':
            return JsonTokenType::END_OBJECT;
        case '[':
            return JsonTokenType::BEGIN_ARRAY;
        case ']':
            return JsonTokenType::END_ARRAY;
        case ':':
            return JsonTokenType::NAME_SEPARATOR;
        case ',':
            return JsonTokenType::VALUE_SEPARATOR;
        case 't':
            scanTrue();
            return JsonTokenType::LITERAL_TRUE;
        case 'f':
            scanFalse();
            return JsonTokenType::LITERAL_FALSE;
        case 'n':
            scanNull();
            return JsonTokenType::LITERAL_NULL;
        case ' ':
        case '\n':
        case '\t':
        case '\r':
            return scan();
        case '\"':
            scanString();
            return JsonTokenType::VALUE_STRING;
        default:
            if (isdigit(c) || c == '-') {
                scanNumber();
                return JsonTokenType::VALUE_NUMBER;
            }
    }
    throw std::logic_error("Unexpected Token: " + c);
}

} // namespace zson