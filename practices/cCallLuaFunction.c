#include <stdio.h>
#include <string.h>
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

/*
#define lua_pop(L,n)		lua_settop(L, -(n)-1)
void lua_settop (lua_State *L, int index);
Accepts any acceptable index, or 0, and sets the stack top to this index. If the new top is larger than the old one, then the new elements are filled with nil. If index is 0, then all stack elements are removed.
*/

const char *lua_function_code = "function add(x, y) return x + y end";

void
call_function(lua_State *L) {
	// luaL_dostring = luaL_loadstring() || lua_pcall()
	if (luaL_dostring(L, lua_function_code)) {
		printf("Failed to run lua code.\n");
		return;
	}
	double x = 1.0, y = 2.3;
	lua_getglobal(L, "add");
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);

	// 下面的第二个参数表示带调用的lua函数存在两个参数。
	// 第三个参数表示即使带调用的函数存在多个返回值，那么也只有一个在执行后会被压入栈中
	// lua_pcall 调用后，虚拟栈中的函数参数和函数名均被弹出。
	if (lua_pcall(L, 2, 1, 0)) {
		printf("error is %s.\n", lua_tostring(L, -1));
		return;
	}
	// 此时结果已经被压入栈中。
	if (!lua_isnumber(L, -1)) {
		printf("function 'add' must return a number.\n");
		return;
	}
	double ret = lua_tonumber(L, -1);
	lua_pop(L, -1);	// 弹出返回值。
	printf("The result of call function is %f.\n", ret);
}

int
main() {
	lua_State *L = luaL_newstate();
	call_function(L);
	lua_close(L);
	return 0;
}