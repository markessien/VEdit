
VEditps.dll: dlldata.obj VEdit_p.obj VEdit_i.obj
	link /dll /out:VEditps.dll /def:VEditps.def /entry:DllMain dlldata.obj VEdit_p.obj VEdit_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del VEditps.dll
	@del VEditps.lib
	@del VEditps.exp
	@del dlldata.obj
	@del VEdit_p.obj
	@del VEdit_i.obj
