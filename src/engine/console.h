#pragma once

extern float conscale;

void processkey(int code, bool isdown);
void processtextinput(const char *str, int len);
float rendercommand(float x, float y, float w);
float renderfullconsole(float w, float h);
float renderconsole(float w, float h, float abovehud);
void conoutf(const char *s, ...) PRINTFARGS(1, 2);
void conoutf(int type, const char *s, ...) PRINTFARGS(2, 3);
void resetcomplete();
void complete(char *s, int maxlen, const char *cmdprefix);
const char *getkeyname(int code);
const char *addreleaseaction(char *s);
tagval *addreleaseaction(ident *id, int numargs);
void writebinds(stream *f);
void writecompletions(stream *f);