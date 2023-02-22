template <typename stl, typename pred_f>
stl myfilter (stl &v, pred_f func)
{
    stl new_v;
    for (typename stl::iterator it = v.begin(); it != v.end(); it++) {
        if (func(*it)) {
            new_v.insert(new_v.end(), *it);
        }
    }
    return new_v;
}