

// #include <cstdio>
// #include <zlang.h>
#include <zen/function.h>
// #include <zen/algorithm.h>

// #include <zen/function/is_callable.h>
// #include <zen/function/fix.h>
// #include <zen/function/pipable.h>
// #include <zen/function/partial.h>
// #include <zen/function/compose.h>
// #include <zen/function/always.h>
// #include <zen/function/regular.h>
// #include <zen/function/implicit.h>
// #include <zen/function/lazy.h>
// #include <zen/function/general.h>
// #include <zen/function/overload.h>
// #include <zen/function/identity.h>
// #include <zen/function/reveal.h>
// #include <zen/function/builder.h>


//#include <zen/traits.h>
//#include <boost/range/begin.hpp>
//#include <boost/range/end.hpp>
//
//#include <boost/fusion/algorithm/iteration/fold.hpp>
//#include <numeric>


#include <zen/test.h>

// #include <zlang.h>

// $(function(sum)(x, y)(x + y));

//ZEN_FUNCTION_OBJECT((sum)(x, y)(x + y));

// struct always_true
// : boost::true_type
// {};

// ZEN_FUNCTION_OBJECT((sum) (x, y) if(always_true)(x + y) else if(always_true)(x + y));

// ZEN_FUNCTION_PIPE_OBJECT((sum_pipe)(x, y)(x + y));

//namespace zen {
//ZEN_FUNCTION_PIPE_OBJECT((fold)(auto r, const init, f)
//     if(is_range<r>)(std::accumulate(boost::begin(r), boost::end(r), init, f))
//     else if(is_sequence<r>)(boost::fusion::fold(r, init, f))
//     def(auto r, f)
//     if (is_range<r>)(std::accumulate(++boost::begin(r), boost::end(r), *boost::begin(r), f))
//     )
//}

//namespace zen {
//    
//struct zen_private_conditional_0zen_class_fold
//{
//    typedef void zen_is_callable_by_result_tag; template<class Zen_X, class Zen_Enable = void> struct enable; template<class Zen_X, class r, class init, class f> struct enable<Zen_X(r, init, f), typename boost::enable_if<zen::requires_detail::requires_<boost::mpl::vector<is_range<r> > > >::type>
//    {
//        typedef void type;
//    };
//    template<class Zen_X, class Zen_Enable = void> struct result; template<class Zen_X, class Zen_Tr, class Zen_Tinit, class Zen_Tf> struct result<Zen_X(Zen_Tr, Zen_Tinit, Zen_Tf), typename enable<Zen_X(typename boost::decay<Zen_Tr>::type, typename boost::decay<Zen_Tinit>::type, typename boost::decay<Zen_Tf>::type)>::type>
//    {
//        static Zen_Tr r; static Zen_Tinit init; static Zen_Tf f; typedef decltype(((std::accumulate(boost::begin(r), boost::end(r), init, f)))) type;
//    };
//    template<class Zen_Tr, class Zen_Tinit, class Zen_Tf> typename result<void(Zen_Tr r, Zen_Tinit init, Zen_Tf f)>::type operator()(Zen_Tr r, Zen_Tinit init, Zen_Tf f)
//    {
//        return (std::accumulate(boost::begin(r), boost::end(r), init, f));
//    }
//};
//struct zen_private_conditional_1zen_class_fold
//{
//    typedef void zen_is_callable_by_result_tag; template<class Zen_X, class Zen_Enable = void> struct enable; template<class Zen_X, class r, class init, class f> struct enable<Zen_X(r, init, f), typename boost::enable_if<zen::requires_detail::requires_<boost::mpl::vector<is_sequence<r> > > >::type>
//    {
//        typedef void type;
//    };
//    template<class Zen_X, class Zen_Enable = void> struct result; template<class Zen_X, class Zen_Tr, class Zen_Tinit, class Zen_Tf> struct result<Zen_X(Zen_Tr, Zen_Tinit, Zen_Tf), typename enable<Zen_X(typename boost::decay<Zen_Tr>::type, typename boost::decay<Zen_Tinit>::type, typename boost::decay<Zen_Tf>::type)>::type>
//    {
//        static Zen_Tr r; static Zen_Tinit init; static Zen_Tf f; typedef decltype(((boost::fusion::fold(r, init, f)))) type;
//    };
//    template<class Zen_Tr, class Zen_Tinit, class Zen_Tf> typename result<void(Zen_Tr r, Zen_Tinit init, Zen_Tf f)>::type operator()(Zen_Tr r, Zen_Tinit init, Zen_Tf f)
//    {
//        return (boost::fusion::fold(r, init, f));
//    }
//};
//typedef zen::conditional_adaptor< zen_private_conditional_0zen_class_fold , zen_private_conditional_1zen_class_fold > zen_private_function_class_0zen_class_fold;
//struct zen_private_conditional_0zen_class_fold
//{
//    typedef void zen_is_callable_by_result_tag; template<class Zen_X, class Zen_Enable = void> struct enable; template<class Zen_X, class r, class f> struct enable<Zen_X(r, f), typename boost::enable_if<zen::requires_detail::requires_<boost::mpl::vector<is_range<r> > > >::type>
//    {
//        typedef void type;
//    };
//    template<class Zen_X, class Zen_Enable = void> struct result; template<class Zen_X, class Zen_Tr, class Zen_Tf> struct result<Zen_X(Zen_Tr, Zen_Tf), typename enable<Zen_X(typename boost::decay<Zen_Tr>::type, typename boost::decay<Zen_Tf>::type)>::type>
//    {
//        static Zen_Tr r; static Zen_Tf f; typedef decltype(((std::accumulate(++boost::begin(r), boost::end(r), *boost::begin(r), f)))) type;
//    };
//    template<class Zen_Tr, class Zen_Tf> typename result<void(Zen_Tr r, Zen_Tf f)>::type operator()(Zen_Tr r, Zen_Tf f)
//    {
//        return (std::accumulate(++boost::begin(r), boost::end(r), *boost::begin(r), f));
//    }
//};
//typedef zen::conditional_adaptor< zen_private_conditional_0zen_class_fold > zen_private_function_class_1zen_class_fold; typedef zen::overload_adaptor< zen_private_function_class_0zen_class_fold , zen_private_function_class_1zen_class_fold > zen_class_fold; zen::static_<zen::pipable_adaptor<zen_class_fold > > fold =
//{
//};
//}


int main()
{
    // int i = sum(5, 3);
    // int ii = sum_pipe(5, 3);
    zen::test::run();
    printf("Tests run\n");
    return 0;
}
