
SHELL = /bin/sh

# V=0 quiet, V=1 verbose.  other values don't work.
V = 0
Q1 = $(V:1=)
Q = $(Q1:0=@)
n=$(NULLCMD)
ECHO1 = $(V:1=@$n)
ECHO = $(ECHO1:0=@echo)

#### Start of system configuration section. ####

srcdir = .
topdir = /usr/include/ruby-1.9.1
hdrdir = /usr/include/ruby-1.9.1
arch_hdrdir = /usr/include/ruby-1.9.1/$(arch)
VPATH = $(srcdir):$(arch_hdrdir)/ruby:$(hdrdir)/ruby

prefix = $(DESTDIR)/usr

rubylibprefix = $(libdir)/$(RUBY_BASE_NAME)

exec_prefix = $(prefix)

vendorhdrdir = $(rubyhdrdir)/vendor_ruby

sitehdrdir = $(rubyhdrdir)/site_ruby

rubyhdrdir = $(includedir)/$(RUBY_BASE_NAME)-$(ruby_version)

vendordir = $(DESTDIR)/usr/lib/ruby/vendor_ruby

sitedir = $(DESTDIR)/usr/local/lib/site_ruby

ridir = $(datarootdir)/$(RI_BASE_NAME)

mandir = $(prefix)/share/man

localedir = $(datarootdir)/locale

libdir = $(exec_prefix)/lib

psdir = $(docdir)

pdfdir = $(docdir)

dvidir = $(docdir)

htmldir = $(docdir)

infodir = $(prefix)/share/info

docdir = $(datarootdir)/doc/$(PACKAGE)

oldincludedir = $(DESTDIR)/usr/include

includedir = $(prefix)/include

localstatedir = $(DESTDIR)/var

sharedstatedir = $(prefix)/com

sysconfdir = $(DESTDIR)/etc

datadir = $(datarootdir)

datarootdir = $(prefix)/share

libexecdir = $(prefix)/lib/ruby1.9.1

sbindir = $(exec_prefix)/sbin

bindir = $(exec_prefix)/bin

rubylibdir = $(rubylibprefix)/$(ruby_version)

archdir = $(rubylibdir)/$(arch)

sitelibdir = $(sitedir)/$(ruby_version)

sitearchdir = $(sitelibdir)/$(sitearch)

vendorlibdir = $(vendordir)/$(ruby_version)

vendorarchdir = $(vendorlibdir)/$(sitearch)


NULLCMD = :

CC = gcc
CXX = g++
LIBRUBY = $(LIBRUBY_SO)
LIBRUBY_A = lib$(RUBY_SO_NAME)-static.a
LIBRUBYARG_SHARED = -l$(RUBY_SO_NAME)
LIBRUBYARG_STATIC = -lruby-1.9.1-static
OUTFLAG = -o 
COUTFLAG = -o 

RUBY_EXTCONF_H = 
cflags   =  $(optflags) $(debugflags) $(warnflags)
optflags = -O3
debugflags = -ggdb
warnflags = -Wextra -Wno-unused-parameter -Wno-parentheses -Wno-long-long -Wno-missing-field-initializers -Wpointer-arith -Wwrite-strings -Wdeclaration-after-statement -Wimplicit-function-declaration
CFLAGS   = -fPIC -fno-strict-aliasing -g -g -O2 -fPIC -frounding-math  
INCFLAGS = -I. -I$(arch_hdrdir) -I$(hdrdir)/ruby/backward -I$(hdrdir) -I$(srcdir)
DEFS     = 
CPPFLAGS =  -ICGAL/IO -I/usr/include/qt3  $(DEFS) $(cppflags)  -I/var/lib/gems/1.9.1/gems/rice-1.4.3/ruby/lib/include
CXXFLAGS = $(CFLAGS)  -Wall -g
ldflags  = -L.  -rdynamic -Wl,-export-dynamic  -L/var/lib/gems/1.9.1/gems/rice-1.4.3/ruby/lib/lib
dldflags = 
ARCH_FLAG = 
DLDFLAGS = $(ldflags) $(dldflags)
LDSHARED = g++ -shared
LDSHAREDXX = $(CXX) -shared
AR = ar
EXEEXT = 

RUBY_BASE_NAME = ruby
RUBY_INSTALL_NAME = ruby1.9.1
RUBY_SO_NAME = ruby-1.9.1
arch = x86_64-linux
sitearch = $(arch)
ruby_version = 1.9.1
ruby = /usr/bin/ruby1.9.1
RUBY = $(ruby)
RM = rm -f
RM_RF = $(RUBY) -run -e rm -- -rf
RMDIRS = rmdir --ignore-fail-on-non-empty -p
MAKEDIRS = /bin/mkdir -p
INSTALL = /usr/bin/install -c
INSTALL_PROG = $(INSTALL) -m 0755
INSTALL_DATA = $(INSTALL) -m 644
COPY = cp

#### End of system configuration section. ####

preload = 


CXX = g++

libpath = . $(libdir) /home/rodrigo/CGAL-4.0.2/lib /usr/share/qt3/lib
LIBPATH =  -L. -L$(libdir) -L/home/rodrigo/CGAL-4.0.2/lib -L/usr/share/qt3/lib
DEFFILE = 

CLEANFILES = mkmf.log
DISTCLEANFILES = 
DISTCLEANDIRS = 

extout = 
extout_prefix = 
target_prefix = 
LOCAL_LIBS = 
LIBS = -lrice -lruby-1.9.1 -lpthread -lrt -ldl -lcrypt -lm   -lc  -lCGAL -lgmp -lmpfr -lqt-mt  -lGL -lGLU -lglut -lCGAL_Qt3 -lCGAL_Core 
SRCS = rb_Polygon_set_2.cpp rb_Nef_polyhedron_3.cpp rb_SVertex.cpp rb_Lazy_exact_nt.cpp rb_Vertex.cpp rb_Polygon_with_holes_2.cpp rb_Halffacet.cpp cgal.cpp rb_Point_2.cpp rb_Aff_transformation_3.cpp rb_Point_3.cpp rb_X_monotone_curve_2.cpp rb_Offset_polygon_with_holes_2.cpp rb_SHalfedge.cpp rb_Offset_polygon_2.cpp rb_Iso_cuboid_3.cpp rb_Polygon_2.cpp
OBJS = rb_Polygon_set_2.o rb_Nef_polyhedron_3.o rb_SVertex.o rb_Lazy_exact_nt.o rb_Vertex.o rb_Polygon_with_holes_2.o rb_Halffacet.o cgal.o rb_Point_2.o rb_Aff_transformation_3.o rb_Point_3.o rb_X_monotone_curve_2.o rb_Offset_polygon_with_holes_2.o rb_SHalfedge.o rb_Offset_polygon_2.o rb_Iso_cuboid_3.o rb_Polygon_2.o
TARGET = cgal
DLLIB = $(TARGET).so
EXTSTATIC = 
STATIC_LIB = 

BINDIR        = $(bindir)
RUBYCOMMONDIR = $(sitedir)$(target_prefix)
RUBYLIBDIR    = $(sitelibdir)$(target_prefix)
RUBYARCHDIR   = $(sitearchdir)$(target_prefix)
HDRDIR        = $(rubyhdrdir)/ruby$(target_prefix)
ARCHHDRDIR    = $(rubyhdrdir)/$(arch)/ruby$(target_prefix)

TARGET_SO     = $(DLLIB)
CLEANLIBS     = $(TARGET).so 
CLEANOBJS     = *.o  *.bak

all:    $(DLLIB)
static: $(STATIC_LIB)
.PHONY: all install static install-so install-rb
.PHONY: clean clean-so clean-rb

clean-rb-default::
clean-rb::
clean-so::
clean: clean-so clean-rb-default clean-rb
		@-$(RM) $(CLEANLIBS) $(CLEANOBJS) $(CLEANFILES)

distclean-rb-default::
distclean-rb::
distclean-so::
distclean: clean distclean-so distclean-rb-default distclean-rb
		@-$(RM) Makefile $(RUBY_EXTCONF_H) conftest.* mkmf.log
		@-$(RM) core ruby$(EXEEXT) *~ $(DISTCLEANFILES)
		@-$(RMDIRS) $(DISTCLEANDIRS) 2> /dev/null || true

realclean: distclean
install: install-so install-rb

install-so: $(RUBYARCHDIR)
install-so: $(RUBYARCHDIR)/$(DLLIB)
$(RUBYARCHDIR)/$(DLLIB): $(DLLIB)
	@-$(MAKEDIRS) $(@D)
	$(INSTALL_PROG) $(DLLIB) $(@D)
install-rb: pre-install-rb install-rb-default
install-rb-default: pre-install-rb-default
pre-install-rb: Makefile
pre-install-rb-default: Makefile
pre-install-rb-default:
	$(ECHO) installing default cgal libraries
$(RUBYARCHDIR):
	$(Q) $(MAKEDIRS) $@

site-install: site-install-so site-install-rb
site-install-so: install-so
site-install-rb: install-rb

.SUFFIXES: .c .m .cc .mm .cxx .cpp .C .o

.cc.o:
	$(ECHO) compiling $(<)
	$(Q) $(CXX) $(INCFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(COUTFLAG)$@ -c $<

.mm.o:
	$(ECHO) compiling $(<)
	$(Q) $(CXX) $(INCFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(COUTFLAG)$@ -c $<

.cxx.o:
	$(ECHO) compiling $(<)
	$(Q) $(CXX) $(INCFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(COUTFLAG)$@ -c $<

.cpp.o:
	$(ECHO) compiling $(<)
	$(Q) $(CXX) $(INCFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(COUTFLAG)$@ -c $<

.C.o:
	$(ECHO) compiling $(<)
	$(Q) $(CXX) $(INCFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(COUTFLAG)$@ -c $<

.c.o:
	$(ECHO) compiling $(<)
	$(Q) $(CC) $(INCFLAGS) $(CPPFLAGS) $(CFLAGS) $(COUTFLAG)$@ -c $<

.m.o:
	$(ECHO) compiling $(<)
	$(Q) $(CC) $(INCFLAGS) $(CPPFLAGS) $(CFLAGS) $(COUTFLAG)$@ -c $<

$(DLLIB): $(OBJS) Makefile
	$(ECHO) linking shared-object $(DLLIB)
	@-$(RM) $(@)
	$(Q) $(LDSHAREDXX) -o $@ $(OBJS) $(LIBPATH) $(DLDFLAGS) $(LOCAL_LIBS) $(LIBS)



$(OBJS): $(hdrdir)/ruby.h $(hdrdir)/ruby/defines.h $(arch_hdrdir)/ruby/config.h
