 --变量定义
width=1 ;
height=2 ;
--lua函数定义，实现加法
function sum(a,b)
    return a+b ;
end

--[==[
很简单的程序，注意以下两个函数
 int luaL_dofile (lua_State *L, const char *filename)和int luaL_loadfile (lua_State *L, const char *filename);
 luaL_dofile在源码中的定义如下：
#define luaL_dofile(L, fn) \
(luaL_loadfile(L, fn) || lua_pcall(L, 0, LUA_MULTRET, 0))
 所以，如果调用luaL_loadfile 加载lua脚本文件，则不需要再次调用lua_pcall(L, 0, 0, 0);如果是调用luaL_dofile加载，则需要在程序中调用一次lua_pcall(L, 0, 0, 0);
--]==]