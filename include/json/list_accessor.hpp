#ifndef JSON_LIST_ACCESSOR_HPP
#define JSON_LIST_ACCESSOR_HPP

/*
 * JSON - a JSON data structure, parser and serialiser library.
 * Copyright (C) 2014 James Goode.
 */

#include "json.hpp"

namespace json
{
    // T is an accessor type
    template<typename T>
    class list_accessor
    {
        public:
        list_accessor( object& l ) :
            m_list ( boost::get<list>(l) )
        {
        }

        class iterator
        {
            public:
            friend class list_accessor;

            T operator *()
            {
                return T(m_list[m_index]);
            }

            iterator operator ++(int)
            {
                iterator tmp(*this);
                ++(*this);
                return tmp;
            }

            iterator operator ++()
            {
                m_index = m_list.m_list.next_index(m_index);
                return *this;
            }

            bool operator ==( const iterator& o ) const
            {
                return &(m_list.get_object()) == &(o.m_list.get_object()) &&
                    m_index == o.m_index;
            }

            bool operator !=( const iterator& o ) const
            {
                return !(*this == o);
            }

            private:
            iterator( list_accessor<T>& l, int i ) :
                m_list  (l),
                m_index (i)
            {
            }
            list_accessor<T>& m_list;
            int m_index;
        };

        iterator begin()
        {
            if( m_list.size() == 0 )
                return end();

            return iterator(*this, m_list.objects.begin()->first);
        }

        iterator end()
        {
            return iterator(*this, -1);
        }

        const list& get_object() { return m_list; }

        T operator []( const unsigned int k )
        {
            // Construct an accessor for the list type
            return T(m_list[k]);
        }

        unsigned int size() const
        {
            return m_list.size();
        }

        protected:
        T& get( const unsigned int k ) { return T(m_list[k]); }

        private:
        list& m_list;
    };
}

#endif

