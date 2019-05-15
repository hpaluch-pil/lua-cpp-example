// lua_ex.c - How to embed LUA library into C/C++ - example

// EXIT_* constants
#include <stdlib.h>
// printf(3)....
#include <stdio.h>

// uname(2)
#include <sys/utsname.h>

// sysinfo(2) - uptime
#include <sys/sysinfo.h>

// NOTE: C++ must use "lua.hpp", however C must use "lua.h"
#include <lua.hpp>

// custom command uname -m - returns machine name

/*
static int
UnameMachineCmd(
    ClientData dummy,
    Tcl_Interp *interp,
    int objc,        
    Tcl_Obj *const objv[])
{
    struct utsname un;

    if (uname(&un)){
        Tcl_SetObjResult(interp, Tcl_ObjPrintf(
                      "error calling uname(): %s",
                      Tcl_PosixError(interp)));
        return TCL_ERROR;
    } else {
        Tcl_SetObjResult(interp, Tcl_NewStringObj(un.machine, -1) );
        return TCL_OK;
    }
}

static int UptimeSecondsCmd(
	    ClientData dummy,
	    Tcl_Interp *interp,
	    int objc,
	    Tcl_Obj *const objv[])
{
	struct sysinfo in;

    if (sysinfo(&in)){
        Tcl_SetObjResult(interp, Tcl_ObjPrintf(
                      "error calling sysinfo(): %s",
                      Tcl_PosixError(interp)));
        return TCL_ERROR;
    } else {
        Tcl_SetObjResult(interp, Tcl_NewLongObj(in.uptime) );
        return TCL_OK;
    }
}



// add custom commands to Tcl
static int Ex_ExtendTcl (Tcl_Interp *interp) {
	Tcl_CreateObjCommand(
	        interp, "::ex::uname_machine", UnameMachineCmd, NULL, NULL);
	Tcl_CreateObjCommand(
	        interp, "::ex::uptime_seconds", UptimeSecondsCmd, NULL, NULL);
	return TCL_OK;
}
*/

// reports error on LUA call and show error message from stack.
// also pops-out error message from stack.
static int Ex_ReportLuaError(lua_State *ls, const char *fn){
	fprintf(stderr, "Error calling %s(): %s", fn, lua_tostring(ls, -1));
    lua_pop(ls, 1);  /* pops LUA error message from the stack */
	return EXIT_FAILURE;
}

// runs LUA commands in luaCommands, returns EXIT_SUCESS or EXIT_FAILURE
// this call always uses fresh LUA instance
static int Ex_RunLua(const char *luaCommands){
	int rc  = EXIT_FAILURE; // our return value
	int err = 0;            // for errors from LUA calls

	lua_State *ls = luaL_newstate();
	if ( ls == NULL ){
		fprintf(stderr,"luaL_newstate() returned NULL\n");
		goto exit0;
	}

	luaL_openlibs(ls);

	err = luaL_loadstring(ls, luaCommands);
	if (err){
		Ex_ReportLuaError(ls, "luaL_loadstring");
		goto exit1;
	}

	// now there is "luaCommmands" string on LUA stack (!)
	// Verify that it is true.
	if (lua_gettop(ls)!=1){
		fprintf(stderr, "Invalid LUA stack - got %d, expected %d\n", 1, 0);
		goto exit1;
	}

	// this executes our commands
	err = lua_pcall(ls, 0, 0, 0);
	if (err){
		fprintf(stderr, "This LUA command failed:\n%s\n", luaCommands);
		Ex_ReportLuaError(ls, "lua_pcall");
		goto exit1;
	}

	rc = EXIT_SUCCESS;

	exit1:
	// additionally report unbalanced stack
	if ( lua_gettop(ls) ){
		fprintf(stderr, "LUA has unbalanced stack before lua_close() call: %d <> %d",
				lua_gettop(ls), 0);
		rc = EXIT_FAILURE;
	}
	lua_close(ls);

	exit0:
	return rc;
}


int main(int argc, char **argv)
{
	int rc = EXIT_SUCCESS;

	// NOTE: unlike TCL there is no global Init function

	rc = Ex_RunLua("print( 'Hello, world on ' .. 'TODO: uname' .. '!' )");

	if (rc == EXIT_SUCCESS){
		rc = Ex_RunLua("print('System uptime is ',123,' seconds.')");
	}

	// NOTE: unlike TCL there is no global Finalize function
	return rc;
}

