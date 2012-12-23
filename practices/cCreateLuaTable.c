#include <stdio.h>
#include <string.h>
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

void
load(lua_State *L) {
	lua_newtable(L); // creates a new table and pushes it onto the stack. It is equivalent to lua_createtable(L, 0, 0)
	lua_pushnumber(L, 0.3); // pushes a number with value 0.3 onto the stack
	lua_setfield(L, -2, "r"); // does the equivalent to t[k] = v, where t is the value at the given valid index -2, v is the value at the top of the stack. This function pops  the value frome the stack. As in lua, this function may trigger a metamethod for "newindex" event

	lua_pushnumber(L, 0.1);
	lua_setfield(L, -2, "g");

	lua_pushnumber(L, 0.4);
	lua_setfield(L, -3, "b");
	lua_setglobal(L, "background"); // pops a value from the stack and sets it as the new value of global name. It is defined as a macro: #define lua_setglobal(L,s)   lua_setfield(L, LUA_GLOBALSINDEX, s)

	lua_getglobal(L, "background"); // pushes onto the stack the value of the global name.It is defined as a macro: #define lua_getglobal(L,s)  lua_getfield(L, LUA_GLOBALSINDEX, s)
	if (!lua_istable(L, -1)) {
		printf("'background' is not a table.\n");
		return;
	}
	lua_getfield(L, -1, "r"); // pushes onto the stack the value t[k], where t is the value at the given valid index -1. As in lua, this function may trigger a metamethod for the "index" event.
	if (!lua_isnumber(L, -1)) {
		printf("Invalid component in background color.\n");
		return;
	}
	int r = (int)(lua_tonumber(L, -1) * 255);
	lua_pop(L, 1);
	lua_getfield(L, -1, "g");
	if (!lua_isnumber(L, -1)) {
		printf("Invalid component in background color.\n");
		return;
	}
	int g = (int)(lua_tonumber(L, -1) * 255);
	lua_pop(L, 1);

	lua_getfield(L, -1, "b");
	if (!lua_isnumber(L, -1)) {
		printf("Invalid component in background color.\n");
		return;
	}
	int b = (int)(lua_tonumber(L, -1) * 255);
	printf("r = %d, g = %d, b = %d = %d\n", r, g, b);
	lua_pop(L, 1);
	lua_pop(L, 1);

	return;
}

int
main() {
	lua_State *L = luaL_newstate();
	load(L);
	lua_close(L);
	return 0;
}