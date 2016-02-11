// Generated by Bisonc++ V4.09.02 on Thu, 11 Feb 2016 15:40:54 +0530

#ifndef ParserBase_h_included
#define ParserBase_h_included

#include <exception>
#include <vector>
#include <iostream>

// $insert preincludes
#include "ast.h"
#include <memory>

namespace // anonymous
{
    struct PI__;
}


// $insert polymorphic
enum class Tag__
{
    DEREF_ASTNODE,
    IDENTIFIER_ASTNODE,
    FLOAT_CONST,
    INT_CONST,
    ARRAYREF_ASTNODE,
    INT,
    STRING_LITERAL,
    EXP_LIST,
    REF_ASTNODE,
    SEQ_ASTNODE,
    STMT_ASTNODE,
    EXP_ASTNODE,
    FUNCALL_ASTNODE,
    ASS_ASTNODE,
    STMT_LIST,
    STRING,
    OP_ASTNODE1,
    FLOAT,
    OP_ASTNODE2,
    IF_ASTNODE,
    RETURN_ASTNODE,
    EMPTY_ASTNODE,
    POINTER_ASTNODE,
    WHILE_ASTNODE,
    FOR_ASTNODE,
};

namespace Meta__
{
    template <Tag__ tag>
    struct TypeOf;

    template <typename Tp_>
    struct TagOf;

// $insert polymorphicSpecializations
    template <>
    struct TagOf<deref_astnode*>
    {
        static Tag__ const tag = Tag__::DEREF_ASTNODE;
    };

    template <>
    struct TagOf<identifier_astnode*>
    {
        static Tag__ const tag = Tag__::IDENTIFIER_ASTNODE;
    };

    template <>
    struct TagOf<floatconst_astnode*>
    {
        static Tag__ const tag = Tag__::FLOAT_CONST;
    };

    template <>
    struct TagOf<intconst_astnode*>
    {
        static Tag__ const tag = Tag__::INT_CONST;
    };

    template <>
    struct TagOf<arrayref_astnode*>
    {
        static Tag__ const tag = Tag__::ARRAYREF_ASTNODE;
    };

    template <>
    struct TagOf<int>
    {
        static Tag__ const tag = Tag__::INT;
    };

    template <>
    struct TagOf<stringconst_astnode*>
    {
        static Tag__ const tag = Tag__::STRING_LITERAL;
    };

    template <>
    struct TagOf<std::vector<exp_astnode*>>
    {
        static Tag__ const tag = Tag__::EXP_LIST;
    };

    template <>
    struct TagOf<ref_astnode*>
    {
        static Tag__ const tag = Tag__::REF_ASTNODE;
    };

    template <>
    struct TagOf<seq_astnode*>
    {
        static Tag__ const tag = Tag__::SEQ_ASTNODE;
    };

    template <>
    struct TagOf<stmt_astnode*>
    {
        static Tag__ const tag = Tag__::STMT_ASTNODE;
    };

    template <>
    struct TagOf<exp_astnode*>
    {
        static Tag__ const tag = Tag__::EXP_ASTNODE;
    };

    template <>
    struct TagOf<funcall_astnode*>
    {
        static Tag__ const tag = Tag__::FUNCALL_ASTNODE;
    };

    template <>
    struct TagOf<ass_astnode*>
    {
        static Tag__ const tag = Tag__::ASS_ASTNODE;
    };

    template <>
    struct TagOf<std::vector<stmt_astnode*>>
    {
        static Tag__ const tag = Tag__::STMT_LIST;
    };

    template <>
    struct TagOf<std::string>
    {
        static Tag__ const tag = Tag__::STRING;
    };

    template <>
    struct TagOf<op_astnode1*>
    {
        static Tag__ const tag = Tag__::OP_ASTNODE1;
    };

    template <>
    struct TagOf<float>
    {
        static Tag__ const tag = Tag__::FLOAT;
    };

    template <>
    struct TagOf<op_astnode2*>
    {
        static Tag__ const tag = Tag__::OP_ASTNODE2;
    };

    template <>
    struct TagOf<if_astnode*>
    {
        static Tag__ const tag = Tag__::IF_ASTNODE;
    };

    template <>
    struct TagOf<return_astnode*>
    {
        static Tag__ const tag = Tag__::RETURN_ASTNODE;
    };

    template <>
    struct TagOf<empty_astnode*>
    {
        static Tag__ const tag = Tag__::EMPTY_ASTNODE;
    };

    template <>
    struct TagOf<pointer_astnode*>
    {
        static Tag__ const tag = Tag__::POINTER_ASTNODE;
    };

    template <>
    struct TagOf<while_astnode*>
    {
        static Tag__ const tag = Tag__::WHILE_ASTNODE;
    };

    template <>
    struct TagOf<for_astnode*>
    {
        static Tag__ const tag = Tag__::FOR_ASTNODE;
    };

    template <>
    struct TypeOf<Tag__::DEREF_ASTNODE>
    {
        typedef deref_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::IDENTIFIER_ASTNODE>
    {
        typedef identifier_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::FLOAT_CONST>
    {
        typedef floatconst_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::INT_CONST>
    {
        typedef intconst_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::ARRAYREF_ASTNODE>
    {
        typedef arrayref_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::INT>
    {
        typedef int type;
    };

    template <>
    struct TypeOf<Tag__::STRING_LITERAL>
    {
        typedef stringconst_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::EXP_LIST>
    {
        typedef std::vector<exp_astnode*> type;
    };

    template <>
    struct TypeOf<Tag__::REF_ASTNODE>
    {
        typedef ref_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::SEQ_ASTNODE>
    {
        typedef seq_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::STMT_ASTNODE>
    {
        typedef stmt_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::EXP_ASTNODE>
    {
        typedef exp_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::FUNCALL_ASTNODE>
    {
        typedef funcall_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::ASS_ASTNODE>
    {
        typedef ass_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::STMT_LIST>
    {
        typedef std::vector<stmt_astnode*> type;
    };

    template <>
    struct TypeOf<Tag__::STRING>
    {
        typedef std::string type;
    };

    template <>
    struct TypeOf<Tag__::OP_ASTNODE1>
    {
        typedef op_astnode1* type;
    };

    template <>
    struct TypeOf<Tag__::FLOAT>
    {
        typedef float type;
    };

    template <>
    struct TypeOf<Tag__::OP_ASTNODE2>
    {
        typedef op_astnode2* type;
    };

    template <>
    struct TypeOf<Tag__::IF_ASTNODE>
    {
        typedef if_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::RETURN_ASTNODE>
    {
        typedef return_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::EMPTY_ASTNODE>
    {
        typedef empty_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::POINTER_ASTNODE>
    {
        typedef pointer_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::WHILE_ASTNODE>
    {
        typedef while_astnode* type;
    };

    template <>
    struct TypeOf<Tag__::FOR_ASTNODE>
    {
        typedef for_astnode* type;
    };


        // The Base class: 
        // Individual semantic value classes are derived from this class.
        // This class offers a member returning the value's Tag__
        // and two member templates get() offering const/non-const access to
        // the actual semantic value type.
    class Base
    {
        Tag__ d_tag;
    
        protected:
            Base(Tag__ tag);

        public:
            Base(Base const &other) = delete;

            Tag__ tag() const;
    
            template <Tag__ tg_>
            typename TypeOf<tg_>::type &get();
    };
    
        // The class Semantic is derived from Base. It stores a particular
        // semantic value type. 
    template <Tag__ tg_>
    class Semantic: public Base
    {
        typedef typename TypeOf<tg_>::type DataType;
    
        DataType d_data;
    
        public:
                // The default constructor and constructors for 
                // defined data types are available
            Semantic();
            Semantic(DataType const &data);
            Semantic(DataType &&tmp);

            DataType &data();
    };

        // The class Stype wraps the shared_ptr holding a pointer to Base.
        // It becomes the polymorphic STYPE__
        // It also wraps Base's get members, allowing constructions like
        // $$.get<INT> to be used, rather than $$->get<INT>.
        // Its operator= can be used to assign a Semantic *
        // directly to the SType object. The free functions (in the parser's
        // namespace (if defined)) semantic__ can be used to obtain a 
        // Semantic *. 
    struct SType: public std::shared_ptr<Base>
    {
        template <typename Tp_>
        SType &operator=(Tp_ &&value);

        Tag__ tag() const;

            // this get()-member checks for 0-pointer and correct tag 
            // in shared_ptr<Base>, and resets the shared_ptr's Base * 
            // to point to Meta::__Semantic<tg_>() if not
        template <Tag__ tg_>
        typename TypeOf<tg_>::type &get();

            // the data()-member does not check, and may result in a 
            // segfault if used incorrectly
        template <Tag__ tg_>
        typename TypeOf<tg_>::type &data();
    };

}  // namespace Meta__

class ParserBase
{
    public:
// $insert tokens

    // Symbolic tokens:
    enum Tokens__
    {
        VOID = 257,
        INT,
        FLOAT,
        RETURN,
        LE_OP,
        GE_OP,
        EQ_OP,
        NE_OP,
        OR_OP,
        AND_OP,
        INC_OP,
        IF,
        ELSE,
        WHILE,
        FOR,
        INT_CONSTANT,
        FLOAT_CONSTANT,
        STRING_LITERAL,
        IDENTIFIER,
        STRUCT,
        PTR_OP,
    };

// $insert STYPE
    typedef Meta__::SType STYPE__;
	public: static STYPE__  d_val__; 


    private:
        int d_stackIdx__;
        std::vector<size_t>   d_stateStack__;
        std::vector<STYPE__>  d_valueStack__;

    protected:
        enum Return__
        {
            PARSE_ACCEPT__ = 0,   // values used as parse()'s return values
            PARSE_ABORT__  = 1
        };
        enum ErrorRecovery__
        {
            DEFAULT_RECOVERY_MODE__,
            UNEXPECTED_TOKEN__,
        };
        bool        d_debug__;
        size_t      d_nErrors__;
        size_t      d_requiredTokens__;
        size_t      d_acceptedTokens__;
        int         d_token__;
        int         d_nextToken__;
        size_t      d_state__;
        STYPE__    *d_vsp__;
        STYPE__     d_nextVal__;

        ParserBase();

        void ABORT() const;
        void ACCEPT() const;
        void ERROR() const;
        void clearin();
        bool debug() const;
        void pop__(size_t count = 1);
        void push__(size_t nextState);
        void popToken__();
        void pushToken__(int token);
        void reduce__(PI__ const &productionInfo);
        void errorVerbose__();
        size_t top__() const;

    public:
        void setDebug(bool mode);
}; 

inline bool ParserBase::debug() const
{
    return d_debug__;
}

inline void ParserBase::setDebug(bool mode)
{
    d_debug__ = mode;
}

inline void ParserBase::ABORT() const
{
    throw PARSE_ABORT__;
}

inline void ParserBase::ACCEPT() const
{
    throw PARSE_ACCEPT__;
}

inline void ParserBase::ERROR() const
{
    throw UNEXPECTED_TOKEN__;
}

// $insert polymorphicInline
namespace Meta__
{

inline Base::Base(Tag__ tag)
:
    d_tag(tag)
{}

inline Tag__ Base::tag() const
{
    return d_tag;
}

template <Tag__ tg_>
inline Semantic<tg_>::Semantic()
:
    Base(tg_),
    d_data(typename TypeOf<tg_>::type())
{}

template <Tag__ tg_>
inline Semantic<tg_>::Semantic(typename TypeOf<tg_>::type const &data)
:
    Base(tg_),
    d_data(data)
{}

template <Tag__ tg_>
inline Semantic<tg_>::Semantic(typename TypeOf<tg_>::type &&tmp)
:
    Base(tg_),
    d_data(std::move(tmp))
{}

template <Tag__ tg_>
inline typename TypeOf<tg_>::type &Semantic<tg_>::data()
{
    return d_data;
}

template <Tag__ tg_>
inline typename TypeOf<tg_>::type &Base::get()
{
    return static_cast<Semantic<tg_> *>(this)->data();
}

inline Tag__ SType::tag() const
{
    return std::shared_ptr<Base>::get()->tag();
}
    
template <Tag__ tg_>
inline typename TypeOf<tg_>::type &SType::get()
{
                    // if we're not yet holding a (tg_) value, initialize to 
                    // a Semantic<tg_> holding a default value
    if (std::shared_ptr<Base>::get() == 0 || tag() != tg_)
        reset(new Semantic<tg_>());

    return std::shared_ptr<Base>::get()->get<tg_>();
}

template <Tag__ tg_>
inline typename TypeOf<tg_>::type &SType::data()
{
    return std::shared_ptr<Base>::get()->get<tg_>();
}

template <bool, typename Tp_>
struct Assign;

template <typename Tp_>
struct Assign<true, Tp_>
{
    static SType &assign(SType *lhs, Tp_ &&tp);
};

template <typename Tp_>
struct Assign<false, Tp_>
{
    static SType &assign(SType *lhs, Tp_ const &tp);
};

template <>
struct Assign<false, SType>
{
    static SType &assign(SType *lhs, SType const &tp);
};

template <typename Tp_>
inline SType &Assign<true, Tp_>::assign(SType *lhs, Tp_ &&tp)
{
    lhs->reset(new Semantic<TagOf<Tp_>::tag>(std::move(tp)));
    return *lhs;
}

template <typename Tp_>
inline SType &Assign<false, Tp_>::assign(SType *lhs, Tp_ const &tp)
{
    lhs->reset(new Semantic<TagOf<Tp_>::tag>(tp));
    return *lhs;
}

inline SType &Assign<false, SType>::assign(SType *lhs, SType const &tp)
{
    return lhs->operator=(tp);
}

template <typename Tp_>
inline SType &SType::operator=(Tp_ &&rhs) 
{
    return Assign<
                std::is_rvalue_reference<Tp_ &&>::value, 
                typename std::remove_reference<Tp_>::type
           >::assign(this, std::forward<Tp_>(rhs));
}

} // namespace Meta__

// As a convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define Parser ParserBase


#endif


