/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT_LIT = 258,
     BOOL_LIT = 259,
     FLOAT_LIT = 260,
     ID = 261,
     STRING_LIT = 262,
     VAR = 263,
     PAR = 264,
     ANNOTATION = 265,
     ANY = 266,
     ARRAY = 267,
     BOOLTOK = 268,
     CASE = 269,
     COLONCOLON = 270,
     CONSTRAINT = 271,
     DEFAULT = 272,
     DOTDOT = 273,
     ELSE = 274,
     ELSEIF = 275,
     ENDIF = 276,
     ENUM = 277,
     FLOATTOK = 278,
     FUNCTION = 279,
     IF = 280,
     INCLUDE = 281,
     INTTOK = 282,
     LET = 283,
     MAXIMIZE = 284,
     MINIMIZE = 285,
     OF = 286,
     SATISFY = 287,
     OUTPUT = 288,
     PREDICATE = 289,
     RECORD = 290,
     SET = 291,
     SHOW = 292,
     SHOWCOND = 293,
     SOLVE = 294,
     STRING = 295,
     TEST = 296,
     THEN = 297,
     TUPLE = 298,
     TYPE = 299,
     VARIANT_RECORD = 300,
     WHERE = 301
   };
#endif
/* Tokens.  */
#define INT_LIT 258
#define BOOL_LIT 259
#define FLOAT_LIT 260
#define ID 261
#define STRING_LIT 262
#define VAR 263
#define PAR 264
#define ANNOTATION 265
#define ANY 266
#define ARRAY 267
#define BOOLTOK 268
#define CASE 269
#define COLONCOLON 270
#define CONSTRAINT 271
#define DEFAULT 272
#define DOTDOT 273
#define ELSE 274
#define ELSEIF 275
#define ENDIF 276
#define ENUM 277
#define FLOATTOK 278
#define FUNCTION 279
#define IF 280
#define INCLUDE 281
#define INTTOK 282
#define LET 283
#define MAXIMIZE 284
#define MINIMIZE 285
#define OF 286
#define SATISFY 287
#define OUTPUT 288
#define PREDICATE 289
#define RECORD 290
#define SET 291
#define SHOW 292
#define SHOWCOND 293
#define SOLVE 294
#define STRING 295
#define TEST 296
#define THEN 297
#define TUPLE 298
#define TYPE 299
#define VARIANT_RECORD 300
#define WHERE 301




/* Copy the first part of user declarations.  */


#define YYPARSE_PARAM parm
#define YYLEX_PARAM static_cast<ParserState*>(parm)->yyscanner

#include <iostream>
#include <fstream>
#include <sstream>

#include <chuffed/flatzinc/flatzinc.h>
#include <chuffed/flatzinc/parser.tab.h>

#ifdef HAVE_MMAP
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#endif

using namespace std;

int yyparse(void*);
int yylex(YYSTYPE*, void* scanner);
int yylex_init (void** scanner);
int yylex_destroy (void* scanner);
int yyget_lineno (void* scanner);
void yyset_extra (void* user_defined ,void* yyscanner );

extern int yydebug;

using namespace FlatZinc;

void yyerror(void* parm, const char *str) {
    ParserState* pp = static_cast<ParserState*>(parm);
    pp->err << "Error: " << str
            << " in line no. " << yyget_lineno(pp->yyscanner)
            << std::endl;
    pp->hadError = true;
}

void yyassert(ParserState* pp, bool cond, const char* str)
{
    if (!cond) {
        pp->err << "Error: " << str
                << " in line no. " << yyget_lineno(pp->yyscanner)
                << std::endl;
        pp->hadError = true;
    }
}

/*
 * The symbol tables
 *
 */

AST::Node* getArrayElement(ParserState* pp, string id, unsigned int offset) {
    if (offset > 0) {
        vector<int> tmp;
        if (pp->intvararrays.get(id, tmp) && offset<= tmp.size())
            return new AST::IntVar(tmp[offset-1]);
        if (pp->boolvararrays.get(id, tmp) && offset<= tmp.size())
            return new AST::BoolVar(tmp[offset-1]);
        if (pp->setvararrays.get(id, tmp) && offset<= tmp.size())
            return new AST::SetVar(tmp[offset-1]);

        if (pp->intvalarrays.get(id, tmp) && offset<= tmp.size())
            return new AST::IntLit(tmp[offset-1]);
        if (pp->boolvalarrays.get(id, tmp) && offset<= tmp.size())
            return new AST::BoolLit(tmp[offset-1]);
        vector<AST::SetLit> tmpS;
        if (pp->setvalarrays.get(id, tmpS) && offset<= tmpS.size())
            return new AST::SetLit(tmpS[offset-1]);      
    }

    pp->err << "Error: array access to " << id << " invalid"
            << " in line no. "
            << yyget_lineno(pp->yyscanner) << std::endl;
    pp->hadError = true;
    return new AST::IntVar(0); // keep things consistent
}
AST::Node* getVarRefArg(ParserState* pp, string id, bool annotation = false) {
    int tmp;
    if (pp->intvarTable.get(id, tmp))
        return new AST::IntVar(tmp);
    if (pp->boolvarTable.get(id, tmp))
        return new AST::BoolVar(tmp);
    if (pp->setvarTable.get(id, tmp))
        return new AST::SetVar(tmp);
    if (annotation)
        return new AST::Atom(id);
    pp->err << "Error: undefined variable " << id
            << " in line no. "
            << yyget_lineno(pp->yyscanner) << std::endl;
    pp->hadError = true;
    return new AST::IntVar(0); // keep things consistent
}

void addDomainConstraint(
    ParserState* pp, std::string id, AST::Node* var, Option<AST::SetLit* >& dom
) {
    if (!dom())
        return;
    AST::Array* args = new AST::Array(2);
    args->a[0] = var;
    args->a[1] = dom.some();
    pp->domainConstraints.push_back(new ConExpr(id, args));
}

/*
 * Initialize the root gecode space
 *
 */

void initfg(ParserState* pp) {
#if EXPOSE_INT_LITS
    static struct {
        const char *int_CMP_reif;
        IntRelType irt;
    } int_CMP_table[] = {
        { "int_eq_reif", IRT_EQ },
        { "int_ne_reif", IRT_NE },
        { "int_ge_reif", IRT_GE },
        { "int_gt_reif", IRT_GT },
        { "int_le_reif", IRT_LE },
        { "int_lt_reif", IRT_LT }
    };

    for (int i = 0; i < static_cast<int>(pp->domainConstraints2.size()); ) {
        ConExpr& c = *pp->domainConstraints2[i].first;
        for (int j = 0; j < 6; ++j)
            if (c.id.compare(int_CMP_table[j].int_CMP_reif) == 0) {
                if (!c[2]->isBoolVar())
                    goto not_found;
                int k;
                for (k = c[2]->getBoolVar(); pp->boolvars[k].second->alias; k = pp->boolvars[k].second->i)
                    ;
                BoolVarSpec& boolvar = *static_cast<BoolVarSpec *>(pp->boolvars[k].second);
                if (boolvar.alias_var >= 0)
                    goto not_found;
                if (c[0]->isIntVar() && c[1]->isInt(boolvar.alias_val)) {
                    boolvar.alias_var = c[0]->getIntVar();
                    boolvar.alias_irt = int_CMP_table[j].irt;
                    goto found;
                }
                if (c[1]->isIntVar() && c[0]->isInt(boolvar.alias_val)) {
                    boolvar.alias_var = c[1]->getIntVar();
                    boolvar.alias_irt = -int_CMP_table[j].irt;
                    goto found;
                }
            }
    not_found:
        ++i;
        continue;
    found:
        delete pp->domainConstraints2[i].first;
        delete pp->domainConstraints2[i].second;
        pp->domainConstraints2.erase(pp->domainConstraints2.begin() + i);
    }
#endif

    if (!pp->hadError)
        pp->fg = new FlatZincSpace(pp->intvars.size(),
                                   pp->boolvars.size(),
                                   pp->setvars.size());

    for (unsigned int i = 0; i < pp->intvars.size(); i++) {
        if (!pp->hadError) {
            try {
                pp->fg->newIntVar(static_cast<IntVarSpec*>(pp->intvars[i].second));
                IntVar* newiv = pp->fg->iv[pp->fg->intVarCount-1];
                intVarString.insert(std::pair<IntVar*, std::string>(newiv, pp->intvars[i].first));
            } catch (FlatZinc::Error& e) {
                yyerror(pp, e.toString().c_str());
            }
        }
        if (pp->intvars[i].first[0] != '[') {
            delete pp->intvars[i].second;
            pp->intvars[i].second = NULL;
        }
    }
    for (unsigned int i = 0; i < pp->boolvars.size(); i++) {
        if (!pp->hadError) {
            try {
                pp->fg->newBoolVar(static_cast<BoolVarSpec*>(pp->boolvars[i].second));
                BoolView newiv = pp->fg->bv[pp->fg->boolVarCount-1];
                if (pp->boolvars[i].second->assigned)
                    boolVarString.insert(std::pair<BoolView, std::string>(newiv, "ASSIGNED_AT_ROOT"));
                else
                    boolVarString.insert(std::pair<BoolView, std::string>(newiv, pp->boolvars[i].first));
                string label;
                label = pp->boolvars[i].first;
                label.append("=true");
                litString.insert(std::pair<int,std::string>(toInt(newiv.getLit(true)), label));
                label = pp->boolvars[i].first;
                label.append("=false");
                litString.insert(std::pair<int,std::string>(toInt(newiv.getLit(false)), label));
            } catch (FlatZinc::Error& e) {
                yyerror(pp, e.toString().c_str());
            }
        }
        if (pp->boolvars[i].first[0] != '[') {
            delete pp->boolvars[i].second;
            pp->boolvars[i].second = NULL;
        }
    }
    for (unsigned int i = 0; i < pp->setvars.size(); i++) {
        if (!pp->hadError) {
            try {
                pp->fg->newSetVar(static_cast<SetVarSpec*>(pp->setvars[i].second));
            } catch (FlatZinc::Error& e) {
                yyerror(pp, e.toString().c_str());
            }
        }            
        if (pp->setvars[i].first[0] != '[') {
            delete pp->setvars[i].second;
            pp->setvars[i].second = NULL;
        }
    }
    for (unsigned int i = pp->domainConstraints.size(); i--;) {
        if (!pp->hadError) {
            try {
                assert(pp->domainConstraints[i]->args->a.size() == 2);
                pp->fg->postConstraint(*pp->domainConstraints[i], NULL);
                delete pp->domainConstraints[i];
            } catch (FlatZinc::Error& e) {
                yyerror(pp, e.toString().c_str());              
            }
        }
    }
#if EXPOSE_INT_LITS
    for (int i = 0; i < static_cast<int>(pp->domainConstraints2.size()); ++i) {
        if (!pp->hadError) {
            try {
                pp->fg->postConstraint(*pp->domainConstraints2[i].first, pp->domainConstraints2[i].second);
                delete pp->domainConstraints2[i].first;
                delete pp->domainConstraints2[i].second;
            } catch (FlatZinc::Error& e) {
                yyerror(pp, e.toString().c_str());              
            }
        }
    }
#endif
}

AST::Node* arrayOutput(AST::Call* ann) {
    AST::Array* a = NULL;
    
    if (ann->args->isArray()) {
        a = ann->args->getArray();
    } else {
        a = new AST::Array(ann->args);
    }
    
    std::ostringstream oss;
    
    oss << "array" << a->a.size() << "d(";
    for (unsigned int i = 0; i < a->a.size(); i++) {
        AST::SetLit* s = a->a[i]->getSet();
        if (s->empty())
            oss << "{}, ";
        else if (s->interval)
            oss << s->min << ".." << s->max << ", ";
        else {
            oss << "{";
            for (unsigned int j = 0; j < s->s.size(); j++) {
                oss << s->s[j];
                if (j < s->s.size()-1)
                    oss << ",";
            }
            oss << "}, ";
        }
    }

    if (!ann->args->isArray()) {
        a->a[0] = NULL;
        delete a;
    }
    return new AST::String(oss.str());
}

/*
 * The main program
 *
 */

namespace FlatZinc {

    void solve(const std::string& filename, std::ostream& err) {
#ifdef HAVE_MMAP
        int fd;
        char* data;
        struct stat sbuf;
        fd = open(filename.c_str(), O_RDONLY);
        if (fd == -1) {
            err << "Cannot open file " << filename << endl;
            exit(0);
        }
        if (stat(filename.c_str(), &sbuf) == -1) {
            err << "Cannot stat file " << filename << endl;
            return;          
        }
        data = (char*)mmap((caddr_t)0, sbuf.st_size, PROT_READ, MAP_SHARED, fd,0);
        if (data == (caddr_t)(-1)) {
            err << "Cannot mmap file " << filename << endl;
            return;          
        }

        ParserState pp(data, sbuf.st_size, err);
#else
        std::ifstream file;
        file.open(filename.c_str());
        if (!file.is_open()) {
            err << "Cannot open file " << filename << endl;
            exit(0);
        }
        std::string s = string(istreambuf_iterator<char>(file),
                                                     istreambuf_iterator<char>());
        ParserState pp(s, err);
#endif
        yylex_init(&pp.yyscanner);
        yyset_extra(&pp, pp.yyscanner);
        // yydebug = 1;
        yyparse(&pp);
        FlatZinc::s->output = pp.getOutput();
        FlatZinc::s->setOutput();
        
        if (pp.yyscanner)
            yylex_destroy(pp.yyscanner);
        if (pp.hadError) abort();
    }

    void solve(std::istream& is, std::ostream& err) {
        std::string s = string(istreambuf_iterator<char>(is),
                               istreambuf_iterator<char>());

        ParserState pp(s, err);
        yylex_init(&pp.yyscanner);
        yyset_extra(&pp, pp.yyscanner);
        // yydebug = 1;
        yyparse(&pp);
        FlatZinc::s->output = pp.getOutput();
        FlatZinc::s->setOutput();
        
        if (pp.yyscanner)
            yylex_destroy(pp.yyscanner);
        if (pp.hadError) abort();
    }

}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE

{ 
    int iValue; 
    char* sValue; 
    bool bValue; 
    double dValue;
    std::vector<int>* setValue;
    FlatZinc::AST::SetLit* setLit;
    std::vector<double>* floatSetValue;
    std::vector<FlatZinc::AST::SetLit>* setValueList;
    FlatZinc::Option<FlatZinc::AST::SetLit* > oSet;
    FlatZinc::VarSpec* varSpec;
    FlatZinc::Option<FlatZinc::AST::Node*> oArg;
    std::vector<FlatZinc::VarSpec*>* varSpecVec;
    FlatZinc::Option<std::vector<FlatZinc::VarSpec*>* > oVarSpecVec;
    FlatZinc::AST::Node* arg;
    FlatZinc::AST::Array* argVec;
}
/* Line 193 of yacc.c.  */

	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */


#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   341

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  157
/* YYNRULES -- Number of states.  */
#define YYNSTATES  340

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      48,    49,     2,     2,    50,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    51,    47,
       2,    54,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,    53,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    55,     2,    56,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     9,    10,    12,    15,    19,    20,    22,
      25,    29,    30,    32,    35,    39,    45,    46,    49,    51,
      55,    59,    66,    74,    77,    79,    81,    85,    87,    89,
      91,    95,    97,   101,   108,   115,   122,   131,   138,   145,
     154,   168,   182,   196,   212,   228,   244,   260,   278,   280,
     282,   287,   288,   291,   293,   297,   298,   300,   304,   306,
     308,   313,   314,   317,   319,   323,   327,   329,   331,   336,
     337,   340,   342,   346,   350,   352,   354,   359,   360,   363,
     365,   369,   373,   374,   377,   378,   381,   382,   385,   386,
     389,   396,   400,   407,   411,   416,   418,   422,   426,   428,
     433,   435,   440,   444,   448,   449,   452,   454,   458,   459,
     462,   464,   468,   469,   472,   474,   478,   479,   482,   484,
     488,   490,   494,   496,   500,   501,   504,   506,   508,   510,
     512,   514,   519,   520,   523,   525,   529,   531,   533,   538,
     540,   542,   543,   545,   548,   552,   557,   559,   561,   565,
     567,   571,   573,   575,   577,   579,   581,   586
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      58,     0,    -1,    59,    61,    63,    96,    47,    -1,    -1,
      60,    -1,    65,    47,    -1,    60,    65,    47,    -1,    -1,
      62,    -1,    73,    47,    -1,    62,    73,    47,    -1,    -1,
      64,    -1,    95,    47,    -1,    64,    95,    47,    -1,    34,
       6,    48,    66,    49,    -1,    -1,    67,    77,    -1,    68,
      -1,    67,    50,    68,    -1,    69,    51,     6,    -1,    12,
      52,    71,    53,    31,    70,    -1,    12,    52,    71,    53,
      31,     8,    70,    -1,     8,    70,    -1,    70,    -1,    97,
      -1,    36,    31,    97,    -1,    13,    -1,    23,    -1,    72,
      -1,    71,    50,    72,    -1,    27,    -1,     3,    18,     3,
      -1,     8,    97,    51,     6,   117,   111,    -1,     8,    98,
      51,     6,   117,   111,    -1,     8,    99,    51,     6,   117,
     111,    -1,     8,    36,    31,    97,    51,     6,   117,   111,
      -1,    97,    51,     6,   117,    54,   112,    -1,    13,    51,
       6,   117,    54,   112,    -1,    36,    31,    97,    51,     6,
     117,    54,   112,    -1,    12,    52,     3,    18,     3,    53,
      31,     8,    97,    51,     6,   117,    91,    -1,    12,    52,
       3,    18,     3,    53,    31,     8,    98,    51,     6,   117,
      92,    -1,    12,    52,     3,    18,     3,    53,    31,     8,
      99,    51,     6,   117,    93,    -1,    12,    52,     3,    18,
       3,    53,    31,     8,    36,    31,    97,    51,     6,   117,
      94,    -1,    12,    52,     3,    18,     3,    53,    31,    97,
      51,     6,   117,    54,    52,   101,    53,    -1,    12,    52,
       3,    18,     3,    53,    31,    13,    51,     6,   117,    54,
      52,   103,    53,    -1,    12,    52,     3,    18,     3,    53,
      31,    23,    51,     6,   117,    54,    52,   105,    53,    -1,
      12,    52,     3,    18,     3,    53,    31,    36,    31,    97,
      51,     6,   117,    54,    52,   107,    53,    -1,     3,    -1,
       6,    -1,     6,    52,     3,    53,    -1,    -1,    76,    77,
      -1,    74,    -1,    76,    50,    74,    -1,    -1,    50,    -1,
      52,    75,    53,    -1,     5,    -1,     6,    -1,     6,    52,
       3,    53,    -1,    -1,    81,    77,    -1,    79,    -1,    81,
      50,    79,    -1,    52,    80,    53,    -1,     4,    -1,     6,
      -1,     6,    52,     3,    53,    -1,    -1,    85,    77,    -1,
      83,    -1,    85,    50,    83,    -1,    52,    84,    53,    -1,
     100,    -1,     6,    -1,     6,    52,     3,    53,    -1,    -1,
      89,    77,    -1,    87,    -1,    89,    50,    87,    -1,    52,
      88,    53,    -1,    -1,    54,    78,    -1,    -1,    54,    86,
      -1,    -1,    54,    82,    -1,    -1,    54,    90,    -1,    16,
       6,    48,   109,    49,   117,    -1,    16,     6,   117,    -1,
      16,     6,    52,     3,    53,   117,    -1,    39,   117,    32,
      -1,    39,   117,   116,   115,    -1,    27,    -1,    55,   101,
      56,    -1,     3,    18,     3,    -1,    13,    -1,    55,   104,
      77,    56,    -1,    23,    -1,    55,   106,    77,    56,    -1,
      55,   101,    56,    -1,     3,    18,     3,    -1,    -1,   102,
      77,    -1,     3,    -1,   102,    50,     3,    -1,    -1,   104,
      77,    -1,     4,    -1,   104,    50,     4,    -1,    -1,   106,
      77,    -1,     5,    -1,   106,    50,     5,    -1,    -1,   108,
      77,    -1,   100,    -1,   108,    50,   100,    -1,   110,    -1,
     109,    50,   110,    -1,   112,    -1,    52,   113,    53,    -1,
      -1,    54,   112,    -1,     4,    -1,     3,    -1,     5,    -1,
     100,    -1,     6,    -1,     6,    52,   112,    53,    -1,    -1,
     114,    77,    -1,   112,    -1,   114,    50,   112,    -1,     3,
      -1,     6,    -1,     6,    52,     3,    53,    -1,    30,    -1,
      29,    -1,    -1,   118,    -1,    15,   119,    -1,   118,    15,
     119,    -1,     6,    48,   120,    49,    -1,   121,    -1,   119,
      -1,   120,    50,   119,    -1,   122,    -1,    52,   120,    53,
      -1,     4,    -1,     3,    -1,     5,    -1,   100,    -1,     6,
      -1,     6,    52,   122,    53,    -1,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   484,   484,   486,   488,   491,   492,   496,   501,   509,
     510,   514,   519,   527,   528,   535,   537,   539,   542,   543,
     546,   549,   550,   551,   552,   555,   556,   557,   558,   561,
     562,   565,   566,   573,   605,   636,   643,   675,   701,   711,
     724,   781,   832,   840,   894,   907,   920,   928,   943,   947,
     962,   986,   989,   995,  1000,  1006,  1008,  1011,  1017,  1021,
    1036,  1060,  1063,  1069,  1074,  1081,  1087,  1091,  1106,  1130,
    1133,  1139,  1144,  1151,  1154,  1158,  1173,  1197,  1200,  1206,
    1211,  1218,  1225,  1228,  1235,  1238,  1245,  1248,  1255,  1258,
    1264,  1282,  1303,  1326,  1334,  1351,  1355,  1359,  1365,  1369,
    1383,  1384,  1391,  1395,  1404,  1407,  1413,  1418,  1426,  1429,
    1435,  1440,  1448,  1451,  1457,  1462,  1470,  1473,  1479,  1485,
    1497,  1501,  1508,  1512,  1519,  1522,  1528,  1532,  1536,  1540,
    1544,  1593,  1607,  1610,  1616,  1620,  1631,  1652,  1682,  1704,
    1705,  1713,  1716,  1722,  1726,  1733,  1738,  1744,  1748,  1755,
    1759,  1765,  1769,  1773,  1777,  1781,  1824,  1835
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT_LIT", "BOOL_LIT", "FLOAT_LIT", "ID",
  "STRING_LIT", "VAR", "PAR", "ANNOTATION", "ANY", "ARRAY", "BOOLTOK",
  "CASE", "COLONCOLON", "CONSTRAINT", "DEFAULT", "DOTDOT", "ELSE",
  "ELSEIF", "ENDIF", "ENUM", "FLOATTOK", "FUNCTION", "IF", "INCLUDE",
  "INTTOK", "LET", "MAXIMIZE", "MINIMIZE", "OF", "SATISFY", "OUTPUT",
  "PREDICATE", "RECORD", "SET", "SHOW", "SHOWCOND", "SOLVE", "STRING",
  "TEST", "THEN", "TUPLE", "TYPE", "VARIANT_RECORD", "WHERE", "';'", "'('",
  "')'", "','", "':'", "'['", "']'", "'='", "'{'", "'}'", "$accept",
  "model", "preddecl_items", "preddecl_items_head", "vardecl_items",
  "vardecl_items_head", "constraint_items", "constraint_items_head",
  "preddecl_item", "pred_arg_list", "pred_arg_list_head", "pred_arg",
  "pred_arg_type", "pred_arg_simple_type", "pred_array_init",
  "pred_array_init_arg", "vardecl_item", "int_init", "int_init_list",
  "int_init_list_head", "list_tail", "int_var_array_literal", "float_init",
  "float_init_list", "float_init_list_head", "float_var_array_literal",
  "bool_init", "bool_init_list", "bool_init_list_head",
  "bool_var_array_literal", "set_init", "set_init_list",
  "set_init_list_head", "set_var_array_literal",
  "vardecl_int_var_array_init", "vardecl_bool_var_array_init",
  "vardecl_float_var_array_init", "vardecl_set_var_array_init",
  "constraint_item", "solve_item", "int_ti_expr_tail", "bool_ti_expr_tail",
  "float_ti_expr_tail", "set_literal", "int_list", "int_list_head",
  "bool_list", "bool_list_head", "float_list", "float_list_head",
  "set_literal_list", "set_literal_list_head", "flat_expr_list",
  "flat_expr", "non_array_expr_opt", "non_array_expr",
  "non_array_expr_list", "non_array_expr_list_head", "solve_expr",
  "minmax", "annotations", "annotations_head", "annotation",
  "annotation_list", "annotation_expr", "ann_non_array_expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,    59,    40,    41,
      44,    58,    91,    93,    61,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    57,    58,    59,    59,    60,    60,    61,    61,    62,
      62,    63,    63,    64,    64,    65,    66,    66,    67,    67,
      68,    69,    69,    69,    69,    70,    70,    70,    70,    71,
      71,    72,    72,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    74,    74,
      74,    75,    75,    76,    76,    77,    77,    78,    79,    79,
      79,    80,    80,    81,    81,    82,    83,    83,    83,    84,
      84,    85,    85,    86,    87,    87,    87,    88,    88,    89,
      89,    90,    91,    91,    92,    92,    93,    93,    94,    94,
      95,    95,    95,    96,    96,    97,    97,    97,    98,    98,
      99,    99,   100,   100,   101,   101,   102,   102,   103,   103,
     104,   104,   105,   105,   106,   106,   107,   107,   108,   108,
     109,   109,   110,   110,   111,   111,   112,   112,   112,   112,
     112,   112,   113,   113,   114,   114,   115,   115,   115,   116,
     116,   117,   117,   118,   118,   119,   119,   120,   120,   121,
     121,   122,   122,   122,   122,   122,   122,   122
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     0,     1,     2,     3,     0,     1,     2,
       3,     0,     1,     2,     3,     5,     0,     2,     1,     3,
       3,     6,     7,     2,     1,     1,     3,     1,     1,     1,
       3,     1,     3,     6,     6,     6,     8,     6,     6,     8,
      13,    13,    13,    15,    15,    15,    15,    17,     1,     1,
       4,     0,     2,     1,     3,     0,     1,     3,     1,     1,
       4,     0,     2,     1,     3,     3,     1,     1,     4,     0,
       2,     1,     3,     3,     1,     1,     4,     0,     2,     1,
       3,     3,     0,     2,     0,     2,     0,     2,     0,     2,
       6,     3,     6,     3,     4,     1,     3,     3,     1,     4,
       1,     4,     3,     3,     0,     2,     1,     3,     0,     2,
       1,     3,     0,     2,     1,     3,     0,     2,     1,     3,
       1,     3,     1,     3,     0,     2,     1,     1,     1,     1,
       1,     4,     0,     2,     1,     3,     1,     1,     4,     1,
       1,     0,     1,     2,     3,     4,     1,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     4,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     7,     4,     0,     0,     1,     0,     0,
       0,     0,    95,     0,   104,    11,     8,     0,     0,     0,
       5,    16,     0,    98,   100,     0,   104,     0,     0,     0,
       0,     0,     0,   106,     0,    55,     0,     0,    12,     0,
       0,     9,     0,     6,     0,     0,    27,    28,     0,     0,
      55,    18,     0,    24,    25,    97,     0,   110,   114,    55,
      55,     0,     0,     0,     0,   141,     0,    96,    56,   105,
     141,   141,     0,     0,    13,    10,   141,    23,     0,     0,
      15,    56,    17,     0,     0,    56,     0,    56,     0,   141,
     141,   141,     0,     0,     0,   142,     0,   107,     0,     0,
      91,     0,     2,    14,     0,     0,    31,     0,    29,    26,
      19,    20,     0,   111,    99,   115,   101,   124,   124,   124,
       0,   152,   151,   153,   155,   157,     0,   104,   154,   143,
     146,   149,     0,     0,   141,   127,   126,   128,   130,   132,
     129,     0,   120,   122,     0,   140,   139,    93,     0,     0,
       0,     0,     0,   141,     0,    33,    34,    35,     0,     0,
       0,     0,   147,     0,     0,    38,   144,     0,     0,   134,
       0,    55,   141,     0,   141,   136,   137,    94,    37,    32,
      30,     0,   124,   125,     0,   103,     0,   155,     0,     0,
     150,   102,     0,     0,   123,    56,   133,    90,   121,    92,
       0,     0,    21,    36,     0,     0,     0,     0,     0,   145,
     156,   148,    39,   131,   135,     0,    22,     0,     0,     0,
       0,     0,     0,     0,     0,   138,     0,     0,     0,     0,
     141,   141,     0,   141,     0,   141,   141,   141,     0,     0,
       0,     0,     0,    82,    84,    86,     0,     0,   141,     0,
     141,     0,    40,     0,    41,     0,    42,   108,   112,     0,
     104,    88,    51,    83,    69,    85,    61,    87,     0,    55,
       0,    55,     0,     0,     0,    43,    48,    49,    53,     0,
      55,    66,    67,    71,     0,    55,    58,    59,    63,     0,
      55,    45,   109,    46,   113,   116,    44,    77,    89,     0,
      57,    56,    52,     0,    73,    56,    70,     0,    65,    56,
      62,     0,   118,     0,    55,    75,    79,     0,    55,    74,
       0,    54,     0,    72,     0,    64,    47,    56,   117,     0,
      81,    56,    78,    50,    68,    60,   119,     0,    80,    76
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    15,    16,    37,    38,     5,    49,
      50,    51,    52,    53,   107,   108,    17,   278,   279,   280,
      69,   263,   288,   289,   290,   267,   283,   284,   285,   265,
     316,   317,   318,   298,   252,   254,   256,   275,    39,    72,
      54,    28,    29,   140,    34,    35,   268,    59,   270,    60,
     313,   314,   141,   142,   155,   143,   170,   171,   177,   148,
      94,    95,   162,   163,   130,   131
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -124
static const yytype_int16 yypact[] =
{
       4,    38,    76,    45,     4,    44,    49,  -124,    75,   105,
      60,    72,  -124,   100,   137,   131,    45,   109,   102,   110,
    -124,    27,   151,  -124,  -124,   134,   147,   112,   113,   115,
     164,   163,    14,  -124,   114,   121,   166,   136,   131,   130,
     135,  -124,   178,  -124,   107,   138,  -124,  -124,   155,   139,
     142,  -124,   144,  -124,  -124,  -124,    14,  -124,  -124,   146,
     148,   183,   188,   191,   181,   185,   150,  -124,   199,  -124,
     133,   185,   157,   159,  -124,  -124,   185,  -124,    25,    14,
    -124,    27,  -124,   202,   158,   206,   156,   208,   160,   185,
     185,   185,   211,    61,   161,   196,   212,  -124,    84,   214,
    -124,    17,  -124,  -124,   169,   209,  -124,   -24,  -124,  -124,
    -124,  -124,   218,  -124,  -124,  -124,  -124,   172,   172,   172,
     167,   210,  -124,  -124,    54,  -124,    61,   137,  -124,  -124,
    -124,  -124,    56,    61,   185,   210,  -124,  -124,   177,    56,
    -124,    36,  -124,  -124,   179,  -124,  -124,  -124,   119,    56,
     228,    25,   203,   185,    56,  -124,  -124,  -124,   205,   230,
      61,    18,  -124,    74,   182,  -124,  -124,   189,    56,  -124,
     186,   192,   185,    84,   185,  -124,   193,  -124,  -124,  -124,
    -124,    71,   172,  -124,   106,  -124,    55,   194,   195,    61,
    -124,  -124,    56,   197,  -124,    56,  -124,  -124,  -124,  -124,
     241,   107,  -124,  -124,   132,   198,   200,   216,   201,  -124,
    -124,  -124,  -124,  -124,  -124,   204,  -124,   222,   207,   215,
     219,   248,   249,    14,   250,  -124,    14,   253,   254,   255,
     185,   185,   220,   185,   221,   185,   185,   185,   213,   223,
     256,   224,   257,   225,   226,   227,   217,   231,   185,   232,
     185,   233,  -124,   234,  -124,   235,  -124,   261,   268,   236,
     137,   237,   143,  -124,    12,  -124,     1,  -124,   229,   146,
     239,   148,   242,   240,   243,  -124,  -124,   244,  -124,   245,
     238,  -124,   247,  -124,   251,   252,  -124,   258,  -124,   259,
     263,  -124,  -124,  -124,  -124,    48,  -124,    89,  -124,   271,
    -124,   143,  -124,   272,  -124,    12,  -124,   273,  -124,     1,
    -124,   210,  -124,   262,   264,   265,  -124,   266,   270,  -124,
     269,  -124,   274,  -124,   275,  -124,  -124,    48,  -124,   286,
    -124,    89,  -124,  -124,  -124,  -124,  -124,   276,  -124,  -124
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -124,  -124,  -124,  -124,  -124,  -124,  -124,  -124,   293,  -124,
    -124,   260,  -124,   -43,  -124,   149,   285,     2,  -124,  -124,
     -50,  -124,    -4,  -124,  -124,  -124,     3,  -124,  -124,  -124,
     -25,  -124,  -124,  -124,  -124,  -124,  -124,  -124,   278,  -124,
      -1,   103,   117,   -90,  -123,  -124,  -124,    52,  -124,    53,
    -124,  -124,  -124,   145,  -107,  -112,  -124,  -124,  -124,  -124,
     -57,  -124,   -88,   165,  -124,   162
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      82,    77,    18,   128,   164,   129,   286,   287,    27,    86,
      88,   156,   157,   100,   101,    18,   281,     8,   282,   104,
     165,   121,   122,   123,   187,   125,   151,   169,   105,   152,
       8,    66,   117,   118,   119,    44,   128,   178,     1,    45,
      46,    12,   183,   128,     6,   166,   145,   146,     8,   147,
      47,   311,   106,     9,    12,    84,   193,    10,    11,   135,
     136,   137,   138,    48,   121,   122,   123,   124,   125,    14,
     128,   128,    12,   127,     8,   203,     7,   167,   109,   201,
     212,    13,    14,   214,    46,   172,   173,   135,   136,   137,
     138,    20,   311,    22,    47,   315,   182,    21,    12,   128,
      14,   211,   160,   127,   209,   189,   161,    48,     8,     8,
       8,   127,    30,   126,   204,   197,   127,   199,    23,   205,
      46,   196,   175,    31,   189,   176,    14,   190,    24,   206,
      47,    32,    12,    12,    12,     8,   139,   273,   202,   127,
      33,    25,   207,    48,   127,    23,   276,    36,    93,   277,
      33,    57,    58,    42,    55,    24,    41,    43,   216,    12,
      26,    14,    14,    61,    62,    56,    63,    64,   217,    65,
      67,    68,    70,   238,   239,    71,   241,    74,   243,   244,
     245,    98,    75,   208,    76,    99,    79,    26,    80,    89,
      78,   259,    81,   261,    90,    83,    85,    91,    87,    92,
      93,    96,    97,   218,   102,   312,   103,   319,   111,   112,
     113,   133,   114,   115,   120,   132,   116,   144,   134,   292,
     158,   294,   232,   149,   153,   234,   154,   150,   159,   168,
     302,   179,   174,   185,   181,   306,   184,   336,   191,   194,
     310,   319,   195,   192,   215,   200,   161,   223,   210,   221,
     213,   222,   224,   226,   230,   231,   233,   225,   227,   235,
     236,   237,   248,   250,   328,    57,   228,   246,   332,   257,
     229,   240,   242,    58,   320,   322,   324,   247,   249,   251,
     253,   255,   291,   258,   260,   262,   264,   266,   301,   337,
     272,   274,   293,   296,   295,   297,   299,    19,   300,   303,
     180,    40,   305,   321,   304,   325,   338,   219,   323,   269,
     307,   271,   308,   309,   327,   326,    73,   329,   198,   330,
     331,   220,   333,   188,     0,   186,     0,   334,   335,   339,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110
};

static const yytype_int16 yycheck[] =
{
      50,    44,     3,    93,   127,    93,     5,     6,     9,    59,
      60,   118,   119,    70,    71,    16,     4,     3,     6,    76,
     132,     3,     4,     5,     6,     7,    50,   139,     3,    53,
       3,    32,    89,    90,    91,     8,   126,   149,    34,    12,
      13,    27,   154,   133,     6,   133,    29,    30,     3,    32,
      23,     3,    27,     8,    27,    56,   168,    12,    13,     3,
       4,     5,     6,    36,     3,     4,     5,     6,     7,    55,
     160,   161,    27,    55,     3,   182,     0,   134,    79,     8,
     192,    36,    55,   195,    13,    49,    50,     3,     4,     5,
       6,    47,     3,    18,    23,     6,   153,    48,    27,   189,
      55,   189,    48,    55,    49,    50,    52,    36,     3,     3,
       3,    55,    52,    52,     8,   172,    55,   174,    13,    13,
      13,   171,     3,    51,    50,     6,    55,    53,    23,    23,
      23,    31,    27,    27,    27,     3,    52,   260,   181,    55,
       3,    36,    36,    36,    55,    13,     3,    16,    15,     6,
       3,     4,     5,    51,     3,    23,    47,    47,   201,    27,
      55,    55,    55,    51,    51,    31,    51,     3,    36,     6,
      56,    50,     6,   230,   231,    39,   233,    47,   235,   236,
     237,    48,    47,   184,     6,    52,    31,    55,    49,     6,
      52,   248,    50,   250,     6,    51,    50,     6,    50,    18,
      15,    51,     3,   204,    47,   295,    47,   297,     6,    51,
       4,    15,    56,     5,     3,    54,    56,     3,     6,   269,
      53,   271,   223,    54,     6,   226,    54,    18,    18,    52,
     280,     3,    53,     3,    31,   285,    31,   327,    56,    53,
     290,   331,    50,    54,     3,    52,    52,    31,    53,    51,
      53,    51,    51,    31,     6,     6,     6,    53,    51,     6,
       6,     6,     6,     6,   314,     4,    51,    54,   318,    52,
      51,    51,    51,     5,     3,     3,     3,    54,    54,    54,
      54,    54,    53,    52,    52,    52,    52,    52,    50,     3,
      54,    54,    53,    53,    52,    52,    52,     4,    53,    52,
     151,    16,    50,   301,    53,   309,   331,   204,   305,   257,
      52,   258,    53,    50,    50,    53,    38,    52,   173,    53,
      50,   204,    53,   161,    -1,   160,    -1,    53,    53,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    34,    58,    59,    60,    65,     6,     0,     3,     8,
      12,    13,    27,    36,    55,    61,    62,    73,    97,    65,
      47,    48,    18,    13,    23,    36,    55,    97,    98,    99,
      52,    51,    31,     3,   101,   102,    16,    63,    64,    95,
      73,    47,    51,    47,     8,    12,    13,    23,    36,    66,
      67,    68,    69,    70,    97,     3,    31,     4,     5,   104,
     106,    51,    51,    51,     3,     6,    97,    56,    50,    77,
       6,    39,    96,    95,    47,    47,     6,    70,    52,    31,
      49,    50,    77,    51,    97,    50,    77,    50,    77,     6,
       6,     6,    18,    15,   117,   118,    51,     3,    48,    52,
     117,   117,    47,    47,   117,     3,    27,    71,    72,    97,
      68,     6,    51,     4,    56,     5,    56,   117,   117,   117,
       3,     3,     4,     5,     6,     7,    52,    55,   100,   119,
     121,   122,    54,    15,     6,     3,     4,     5,     6,    52,
     100,   109,   110,   112,     3,    29,    30,    32,   116,    54,
      18,    50,    53,     6,    54,   111,   111,   111,    53,    18,
      48,    52,   119,   120,   101,   112,   119,   117,    52,   112,
     113,   114,    49,    50,    53,     3,     6,   115,   112,     3,
      72,    31,   117,   112,    31,     3,   120,     6,   122,    50,
      53,    56,    54,   112,    53,    50,    77,   117,   110,   117,
      52,     8,    70,   111,     8,    13,    23,    36,    97,    49,
      53,   119,   112,    53,   112,     3,    70,    36,    97,    98,
      99,    51,    51,    31,    51,    53,    31,    51,    51,    51,
       6,     6,    97,     6,    97,     6,     6,     6,   117,   117,
      51,   117,    51,   117,   117,   117,    54,    54,     6,    54,
       6,    54,    91,    54,    92,    54,    93,    52,    52,   117,
      52,   117,    52,    78,    52,    86,    52,    82,   103,   104,
     105,   106,    54,   101,    54,    94,     3,     6,    74,    75,
      76,     4,     6,    83,    84,    85,     5,     6,    79,    80,
      81,    53,    77,    53,    77,    52,    53,    52,    90,    52,
      53,    50,    77,    52,    53,    50,    77,    52,    53,    50,
      77,     3,   100,   107,   108,     6,    87,    88,    89,   100,
       3,    74,     3,    83,     3,    79,    53,    50,    77,    52,
      53,    50,    77,    53,    53,    53,   100,     3,    87,    53
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (parm, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, parm); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void *parm)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, parm)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    void *parm;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (parm);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void *parm)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, parm)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    void *parm;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, parm);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, void *parm)
#else
static void
yy_reduce_print (yyvsp, yyrule, parm)
    YYSTYPE *yyvsp;
    int yyrule;
    void *parm;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , parm);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, parm); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *parm)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, parm)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    void *parm;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (parm);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void *parm);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *parm)
#else
int
yyparse (parm)
    void *parm;
#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 7:

    {
#if !EXPOSE_INT_LITS
            initfg(static_cast<ParserState*>(parm));
#endif
        ;}
    break;

  case 8:

    {
#if !EXPOSE_INT_LITS
            initfg(static_cast<ParserState*>(parm));
#endif
        ;}
    break;

  case 11:

    {
#if EXPOSE_INT_LITS
            initfg(static_cast<ParserState*>(parm));
#endif
        ;}
    break;

  case 12:

    {
#if EXPOSE_INT_LITS
            initfg(static_cast<ParserState*>(parm));
#endif
        ;}
    break;

  case 33:

    {
            ParserState* pp = static_cast<ParserState*>(parm);
            yyassert(pp, !(yyvsp[(2) - (6)].oSet)() || !(yyvsp[(2) - (6)].oSet).some()->empty(), "Empty var int domain.");
            bool print = (yyvsp[(5) - (6)].argVec) && (yyvsp[(5) - (6)].argVec)->hasAtom("output_var");
            pp->intvarTable.put((yyvsp[(4) - (6)].sValue), pp->intvars.size());
            if (print) {
                pp->output(std::string((yyvsp[(4) - (6)].sValue)), new AST::IntVar(pp->intvars.size()));
            }
            bool introduced = (yyvsp[(5) - (6)].argVec) && (yyvsp[(5) - (6)].argVec)->hasAtom("var_is_introduced");
            bool looks_introduced = (strncmp((yyvsp[(4) - (6)].sValue), "X_INTRODUCED_", 13) == 0);
            if ((yyvsp[(6) - (6)].oArg)()) {
                AST::Node* arg = (yyvsp[(6) - (6)].oArg).some();
                if (arg->isInt()) {
                    pp->intvars.push_back(varspec((yyvsp[(4) - (6)].sValue),
                        new IntVarSpec(arg->getInt(),print,introduced,looks_introduced)));
                } else if (arg->isIntVar()) {
                    pp->intvars.push_back(varspec((yyvsp[(4) - (6)].sValue),
                        new IntVarSpec(Alias(arg->getIntVar()),print,introduced,looks_introduced)));
                } else {
                    yyassert(pp, false, "Invalid var int initializer.");
                }
                if (!pp->hadError)
                    addDomainConstraint(pp, "set_in",
                        new AST::IntVar(pp->intvars.size()-1), (yyvsp[(2) - (6)].oSet));
                delete arg;
            } else {
                pp->intvars.push_back(varspec((yyvsp[(4) - (6)].sValue), new IntVarSpec((yyvsp[(2) - (6)].oSet),print,introduced,looks_introduced)));
            }
            delete (yyvsp[(5) - (6)].argVec);
            free((yyvsp[(4) - (6)].sValue));
        ;}
    break;

  case 34:

    {
            ParserState* pp = static_cast<ParserState*>(parm);
            bool print = (yyvsp[(5) - (6)].argVec) && (yyvsp[(5) - (6)].argVec)->hasAtom("output_var");
            pp->boolvarTable.put((yyvsp[(4) - (6)].sValue), pp->boolvars.size());
            if (print) {
                pp->output(std::string((yyvsp[(4) - (6)].sValue)), new AST::BoolVar(pp->boolvars.size()));
            }
            bool introduced = (yyvsp[(5) - (6)].argVec) && (yyvsp[(5) - (6)].argVec)->hasAtom("var_is_introduced");
            bool looks_introduced = (strncmp((yyvsp[(4) - (6)].sValue), "X_INTRODUCED_", 13) == 0);
            if ((yyvsp[(6) - (6)].oArg)()) {
                AST::Node* arg = (yyvsp[(6) - (6)].oArg).some();
                if (arg->isBool()) {
                    pp->boolvars.push_back(varspec((yyvsp[(4) - (6)].sValue),
                        new BoolVarSpec(arg->getBool(),print,introduced,looks_introduced)));                        
                } else if (arg->isBoolVar()) {
                    pp->boolvars.push_back(varspec((yyvsp[(4) - (6)].sValue),
                        new BoolVarSpec(Alias(arg->getBoolVar()),print,introduced,looks_introduced)));
                } else {
                    yyassert(pp, false, "Invalid var bool initializer.");
                }
                if (!pp->hadError)
                    addDomainConstraint(pp, "set_in",
                        new AST::BoolVar(pp->boolvars.size()-1), (yyvsp[(2) - (6)].oSet));
                delete arg;
            } else {
                pp->boolvars.push_back(varspec((yyvsp[(4) - (6)].sValue), new BoolVarSpec((yyvsp[(2) - (6)].oSet),print,introduced,looks_introduced)));
            }
            delete (yyvsp[(5) - (6)].argVec);
            free((yyvsp[(4) - (6)].sValue));
        ;}
    break;

  case 35:

    { 
            ParserState* pp = static_cast<ParserState*>(parm);
            yyassert(pp, false, "Floats not supported.");
            delete (yyvsp[(5) - (6)].argVec);
            free((yyvsp[(4) - (6)].sValue));
        ;}
    break;

  case 36:

    { 
            ParserState* pp = static_cast<ParserState*>(parm);
            bool print = (yyvsp[(7) - (8)].argVec) && (yyvsp[(7) - (8)].argVec)->hasAtom("output_var");
            pp->setvarTable.put((yyvsp[(6) - (8)].sValue), pp->setvars.size());
            if (print) {
                pp->output(std::string((yyvsp[(6) - (8)].sValue)), new AST::SetVar(pp->setvars.size()));
            }
            bool introduced = (yyvsp[(7) - (8)].argVec) && (yyvsp[(7) - (8)].argVec)->hasAtom("var_is_introduced");
            bool looks_introduced = (strncmp((yyvsp[(6) - (8)].sValue), "X_INTRODUCED_", 13) == 0);
            if ((yyvsp[(8) - (8)].oArg)()) {
                AST::Node* arg = (yyvsp[(8) - (8)].oArg).some();
                if (arg->isSet()) {
                    pp->setvars.push_back(varspec((yyvsp[(6) - (8)].sValue),
                        new SetVarSpec(arg->getSet(),print,introduced,looks_introduced)));                      
                } else if (arg->isSetVar()) {
                    pp->setvars.push_back(varspec((yyvsp[(6) - (8)].sValue),
                        new SetVarSpec(Alias(arg->getSetVar()),print,introduced,looks_introduced)));
                    delete arg;
                } else {
                    yyassert(pp, false, "Invalid var set initializer.");
                    delete arg;
                }
                if (!pp->hadError)
                    addDomainConstraint(pp, "set_subset",
                        new AST::SetVar(pp->setvars.size()-1), (yyvsp[(4) - (8)].oSet));
            } else {
                pp->setvars.push_back(varspec((yyvsp[(6) - (8)].sValue), new SetVarSpec((yyvsp[(4) - (8)].oSet),print,introduced,looks_introduced)));
            }
            delete (yyvsp[(7) - (8)].argVec);
            free((yyvsp[(6) - (8)].sValue));
        ;}
    break;

  case 37:

    {
            ParserState* pp = static_cast<ParserState*>(parm);
            yyassert(pp, !(yyvsp[(1) - (6)].oSet)() || !(yyvsp[(1) - (6)].oSet).some()->empty(), "Empty int domain.");
            yyassert(pp, (yyvsp[(6) - (6)].arg)->isInt(), "Invalid int initializer.");
            int i = -1;
            bool isInt = (yyvsp[(6) - (6)].arg)->isInt(i);
            if ((yyvsp[(1) - (6)].oSet)() && isInt) {
                AST::SetLit* sl = (yyvsp[(1) - (6)].oSet).some();
                if (sl->interval) {
                    yyassert(pp, i >= sl->min && i <= sl->max, "Empty int domain.");
                } else {
                    bool found = false;
                    for (unsigned int j = 0; j < sl->s.size(); j++) {
                        if (sl->s[j] == i) {
                            found = true;
                            break;
                        }
                    }
                    yyassert(pp, found, "Empty int domain.");
                }
            }
            pp->intvals.put((yyvsp[(3) - (6)].sValue), i);
            delete (yyvsp[(4) - (6)].argVec);
            free((yyvsp[(3) - (6)].sValue));                
        ;}
    break;

  case 38:

    {
            ParserState* pp = static_cast<ParserState*>(parm);
            yyassert(pp, (yyvsp[(6) - (6)].arg)->isBool(), "Invalid bool initializer.");
            if ((yyvsp[(6) - (6)].arg)->isBool()) {
                pp->boolvals.put((yyvsp[(3) - (6)].sValue), (yyvsp[(6) - (6)].arg)->getBool());
            }
            delete (yyvsp[(4) - (6)].argVec);
            free((yyvsp[(3) - (6)].sValue));                
        ;}
    break;

  case 39:

    {
            ParserState* pp = static_cast<ParserState*>(parm);
            yyassert(pp, !(yyvsp[(3) - (8)].oSet)() || !(yyvsp[(3) - (8)].oSet).some()->empty(), "Empty set domain.");
            yyassert(pp, (yyvsp[(8) - (8)].arg)->isSet(), "Invalid set initializer.");
            AST::SetLit* set = NULL;
            if ((yyvsp[(8) - (8)].arg)->isSet())
                set = (yyvsp[(8) - (8)].arg)->getSet();
            pp->setvals.put((yyvsp[(5) - (8)].sValue), *set);
            delete set;
            delete (yyvsp[(6) - (8)].argVec);
            free((yyvsp[(5) - (8)].sValue));                
        ;}
    break;

  case 40:

    {
            ParserState* pp = static_cast<ParserState*>(parm);
            yyassert(pp, (yyvsp[(3) - (13)].iValue) == 1, "Arrays must start at 1");
            if (!pp->hadError) {
                bool print = (yyvsp[(12) - (13)].argVec) && (yyvsp[(12) - (13)].argVec)->hasCall("output_array");
                vector<int> vars((yyvsp[(5) - (13)].iValue));
                yyassert(pp, !(yyvsp[(9) - (13)].oSet)() || !(yyvsp[(9) - (13)].oSet).some()->empty(), "Empty var int domain.");
                if (!pp->hadError) {
                    if ((yyvsp[(13) - (13)].oVarSpecVec)()) {
                        vector<VarSpec*>* vsv = (yyvsp[(13) - (13)].oVarSpecVec).some();
                        yyassert(pp, vsv->size() == static_cast<unsigned int>((yyvsp[(5) - (13)].iValue)),
                            "Initializer size does not match array dimension");
                        if (!pp->hadError) {
                            for (int i = 0; i < (yyvsp[(5) - (13)].iValue); i++) {
                                IntVarSpec* ivsv = static_cast<IntVarSpec*>((*vsv)[i]);
                                if (ivsv->alias) {
                                    vars[i] = ivsv->i;
                                } else {
                                    vars[i] = pp->intvars.size();
                                    pp->intvars.push_back(varspec((yyvsp[(11) - (13)].sValue), ivsv));
                                }
                                if (!pp->hadError && (yyvsp[(9) - (13)].oSet)()) {
                                    Option<AST::SetLit*> opt =
                                        Option<AST::SetLit*>::some(new AST::SetLit(*(yyvsp[(9) - (13)].oSet).some()));
                                    addDomainConstraint(pp, "set_in", new AST::IntVar(vars[i]), opt);
                                }
                            }
                        }
                        delete vsv;
                    } else {
                        IntVarSpec* ispec = new IntVarSpec((yyvsp[(9) - (13)].oSet),print,!print,false);
                        string arrayname = "["; arrayname += (yyvsp[(11) - (13)].sValue);
                        for (int i = 0; i < (yyvsp[(5) - (13)].iValue)-1; i++) {
                            vars[i] = pp->intvars.size();
                            pp->intvars.push_back(varspec(arrayname, ispec));
                        }                    
                        vars[(yyvsp[(5) - (13)].iValue)-1] = pp->intvars.size();
                        pp->intvars.push_back(varspec((yyvsp[(11) - (13)].sValue), ispec));
                    }
                }
                if (print) {
                    AST::Array* a = new AST::Array();
                    a->a.push_back(arrayOutput((yyvsp[(12) - (13)].argVec)->getCall("output_array")));
                    AST::Array* output = new AST::Array();
                    for (int i = 0; i < (yyvsp[(5) - (13)].iValue); i++)
                        output->a.push_back(new AST::IntVar(vars[i]));
                    a->a.push_back(output);
                    a->a.push_back(new AST::String(")"));
                    pp->output(std::string((yyvsp[(11) - (13)].sValue)), a);
                }
                pp->intvararrays.put((yyvsp[(11) - (13)].sValue), vars);
            }
            delete (yyvsp[(12) - (13)].argVec);
            free((yyvsp[(11) - (13)].sValue));
        ;}
    break;

  case 41:

    {
            ParserState* pp = static_cast<ParserState*>(parm);
            bool print = (yyvsp[(12) - (13)].argVec) && (yyvsp[(12) - (13)].argVec)->hasCall("output_array");
            yyassert(pp, (yyvsp[(3) - (13)].iValue) == 1, "Arrays must start at 1");
            if (!pp->hadError) {
                vector<int> vars((yyvsp[(5) - (13)].iValue));
                if ((yyvsp[(13) - (13)].oVarSpecVec)()) {
                    vector<VarSpec*>* vsv = (yyvsp[(13) - (13)].oVarSpecVec).some();
                    yyassert(pp, vsv->size() == static_cast<unsigned int>((yyvsp[(5) - (13)].iValue)),
                        "Initializer size does not match array dimension");
                    if (!pp->hadError) {
                        for (int i = 0; i < (yyvsp[(5) - (13)].iValue); i++) {
                            BoolVarSpec* bvsv = static_cast<BoolVarSpec*>((*vsv)[i]);
                            if (bvsv->alias)
                                vars[i] = bvsv->i;
                            else {
                                vars[i] = pp->boolvars.size();
                                pp->boolvars.push_back(varspec((yyvsp[(11) - (13)].sValue), (*vsv)[i]));
                            }
                            if (!pp->hadError && (yyvsp[(9) - (13)].oSet)()) {
                                Option<AST::SetLit*> opt =
                                    Option<AST::SetLit*>::some(new AST::SetLit(*(yyvsp[(9) - (13)].oSet).some()));
                                addDomainConstraint(pp, "set_in", new AST::BoolVar(vars[i]), opt);
                            }
                        }
                    }
                    delete vsv;
                } else {
                    for (int i = 0; i < (yyvsp[(5) - (13)].iValue); i++) {
                        vars[i] = pp->boolvars.size();
                        pp->boolvars.push_back(varspec((yyvsp[(11) - (13)].sValue),
                            new BoolVarSpec((yyvsp[(9) - (13)].oSet),print,!print,false)));
                    }                    
                }
                if (print) {
                    AST::Array* a = new AST::Array();
                    a->a.push_back(arrayOutput((yyvsp[(12) - (13)].argVec)->getCall("output_array")));
                    AST::Array* output = new AST::Array();
                    for (int i = 0; i < (yyvsp[(5) - (13)].iValue); i++)
                        output->a.push_back(new AST::BoolVar(vars[i]));
                    a->a.push_back(output);
                    a->a.push_back(new AST::String(")"));
                    pp->output(std::string((yyvsp[(11) - (13)].sValue)), a);
                }
                pp->boolvararrays.put((yyvsp[(11) - (13)].sValue), vars);
            }
            delete (yyvsp[(12) - (13)].argVec);
            free((yyvsp[(11) - (13)].sValue));
        ;}
    break;

  case 42:

    { 
            ParserState* pp = static_cast<ParserState*>(parm);
            yyassert(pp, false, "Floats not supported.");
            delete (yyvsp[(12) - (13)].argVec);
            free((yyvsp[(11) - (13)].sValue));
        ;}
    break;

  case 43:

    { 
            ParserState* pp = static_cast<ParserState*>(parm);
            bool print = (yyvsp[(14) - (15)].argVec) && (yyvsp[(14) - (15)].argVec)->hasCall("output_array");
            yyassert(pp, (yyvsp[(3) - (15)].iValue) == 1, "Arrays must start at 1");
            if (!pp->hadError) {
                vector<int> vars((yyvsp[(5) - (15)].iValue));
                if ((yyvsp[(15) - (15)].oVarSpecVec)()) {
                    vector<VarSpec*>* vsv = (yyvsp[(15) - (15)].oVarSpecVec).some();
                    yyassert(pp, vsv->size() == static_cast<unsigned int>((yyvsp[(5) - (15)].iValue)),
                        "Initializer size does not match array dimension");
                    if (!pp->hadError) {
                        for (int i = 0; i < (yyvsp[(5) - (15)].iValue); i++) {
                            SetVarSpec* svsv = static_cast<SetVarSpec*>((*vsv)[i]);
                            if (svsv->alias)
                                vars[i] = svsv->i;
                            else {
                                vars[i] = pp->setvars.size();
                                pp->setvars.push_back(varspec((yyvsp[(13) - (15)].sValue), (*vsv)[i]));
                            }
                            if (!pp->hadError && (yyvsp[(11) - (15)].oSet)()) {
                                Option<AST::SetLit*> opt =
                                    Option<AST::SetLit*>::some(new AST::SetLit(*(yyvsp[(11) - (15)].oSet).some()));
                                addDomainConstraint(pp, "set_subset", new AST::SetVar(vars[i]), opt);
                            }
                        }
                    }
                    delete vsv;
                } else {
                    SetVarSpec* ispec = new SetVarSpec((yyvsp[(11) - (15)].oSet),print,!print, false);
                    string arrayname = "["; arrayname += (yyvsp[(13) - (15)].sValue);
                    for (int i = 0; i < (yyvsp[(5) - (15)].iValue)-1; i++) {
                        vars[i] = pp->setvars.size();
                        pp->setvars.push_back(varspec(arrayname, ispec));
                    }                    
                    vars[(yyvsp[(5) - (15)].iValue)-1] = pp->setvars.size();
                    pp->setvars.push_back(varspec((yyvsp[(13) - (15)].sValue), ispec));
                }
                if (print) {
                    AST::Array* a = new AST::Array();
                    a->a.push_back(arrayOutput((yyvsp[(14) - (15)].argVec)->getCall("output_array")));
                    AST::Array* output = new AST::Array();
                    for (int i = 0; i < (yyvsp[(5) - (15)].iValue); i++)
                        output->a.push_back(new AST::SetVar(vars[i]));
                    a->a.push_back(output);
                    a->a.push_back(new AST::String(")"));
                    pp->output(std::string((yyvsp[(13) - (15)].sValue)), a);
                }
                pp->setvararrays.put((yyvsp[(13) - (15)].sValue), vars);
            }
            delete (yyvsp[(14) - (15)].argVec);
            free((yyvsp[(13) - (15)].sValue));
        ;}
    break;

  case 44:

    {
            ParserState* pp = static_cast<ParserState*>(parm);
            yyassert(pp, (yyvsp[(3) - (15)].iValue) == 1, "Arrays must start at 1");
            yyassert(pp, (yyvsp[(14) - (15)].setValue)->size() == static_cast<unsigned int>((yyvsp[(5) - (15)].iValue)),
                             "Initializer size does not match array dimension");
            if (!pp->hadError)
                pp->intvalarrays.put((yyvsp[(10) - (15)].sValue), *(yyvsp[(14) - (15)].setValue));
            delete (yyvsp[(14) - (15)].setValue);
            free((yyvsp[(10) - (15)].sValue));
            delete (yyvsp[(11) - (15)].argVec);
        ;}
    break;

  case 45:

    {
            ParserState* pp = static_cast<ParserState*>(parm);
            yyassert(pp, (yyvsp[(3) - (15)].iValue) == 1, "Arrays must start at 1");
            yyassert(pp, (yyvsp[(14) - (15)].setValue)->size() == static_cast<unsigned int>((yyvsp[(5) - (15)].iValue)),
                             "Initializer size does not match array dimension");
            if (!pp->hadError)
                pp->boolvalarrays.put((yyvsp[(10) - (15)].sValue), *(yyvsp[(14) - (15)].setValue));
            delete (yyvsp[(14) - (15)].setValue);
            free((yyvsp[(10) - (15)].sValue));
            delete (yyvsp[(11) - (15)].argVec);
        ;}
    break;

  case 46:

    {
            ParserState* pp = static_cast<ParserState*>(parm);
            yyassert(pp, false, "Floats not supported.");
            delete (yyvsp[(11) - (15)].argVec);
            free((yyvsp[(10) - (15)].sValue));
        ;}
    break;

  case 47:

    {
            ParserState* pp = static_cast<ParserState*>(parm);
            yyassert(pp, (yyvsp[(3) - (17)].iValue) == 1, "Arrays must start at 1");
            yyassert(pp, (yyvsp[(16) - (17)].setValueList)->size() == static_cast<unsigned int>((yyvsp[(5) - (17)].iValue)),
                             "Initializer size does not match array dimension");
            if (!pp->hadError)
                pp->setvalarrays.put((yyvsp[(12) - (17)].sValue), *(yyvsp[(16) - (17)].setValueList));
            delete (yyvsp[(16) - (17)].setValueList);
            delete (yyvsp[(13) - (17)].argVec);
            free((yyvsp[(12) - (17)].sValue));
        ;}
    break;

  case 48:

    { 
            (yyval.varSpec) = new IntVarSpec((yyvsp[(1) - (1)].iValue), false, true, false);
        ;}
    break;

  case 49:

    { 
            int v = 0;
            ParserState* pp = static_cast<ParserState*>(parm);
            if (pp->intvarTable.get((yyvsp[(1) - (1)].sValue), v))
                (yyval.varSpec) = new IntVarSpec(Alias(v), false, true, false);
            else {
                pp->err << "Error: undefined identifier " << (yyvsp[(1) - (1)].sValue)
                        << " in line no. "
                        << yyget_lineno(pp->yyscanner) << std::endl;
                pp->hadError = true;
                (yyval.varSpec) = new IntVarSpec(0,false,true,false); // keep things consistent
            }
            free((yyvsp[(1) - (1)].sValue));
        ;}
    break;

  case 50:

    { 
            vector<int> v;
            ParserState* pp = static_cast<ParserState*>(parm);
            if (pp->intvararrays.get((yyvsp[(1) - (4)].sValue), v)) {
                yyassert(pp,static_cast<unsigned int>((yyvsp[(3) - (4)].iValue)) > 0 && 
                                        static_cast<unsigned int>((yyvsp[(3) - (4)].iValue)) <= v.size(),
                                 "array access out of bounds");
                if (!pp->hadError)
                    (yyval.varSpec) = new IntVarSpec(Alias(v[(yyvsp[(3) - (4)].iValue)-1]),false,true,false);
                else
                    (yyval.varSpec) = new IntVarSpec(0,false,true,false); // keep things consistent
            } else {
                pp->err << "Error: undefined array identifier " << (yyvsp[(1) - (4)].sValue)
                        << " in line no. "
                        << yyget_lineno(pp->yyscanner) << std::endl;
                pp->hadError = true;
                (yyval.varSpec) = new IntVarSpec(0,false,true,false); // keep things consistent
            }
            free((yyvsp[(1) - (4)].sValue));
        ;}
    break;

  case 51:

    { 
            (yyval.varSpecVec) = new vector<VarSpec*>(0); 
        ;}
    break;

  case 52:

    { 
            (yyval.varSpecVec) = (yyvsp[(1) - (2)].varSpecVec); 
        ;}
    break;

  case 53:

    { 
            (yyval.varSpecVec) = new vector<VarSpec*>(1); 
            (*(yyval.varSpecVec))[0] = (yyvsp[(1) - (1)].varSpec); 
        ;}
    break;

  case 54:

    { 
            (yyval.varSpecVec) = (yyvsp[(1) - (3)].varSpecVec); 
            (yyval.varSpecVec)->push_back((yyvsp[(3) - (3)].varSpec)); 
        ;}
    break;

  case 57:

    { 
            (yyval.varSpecVec) = (yyvsp[(2) - (3)].varSpecVec); 
        ;}
    break;

  case 58:

    { 
            (yyval.varSpec) = new FloatVarSpec((yyvsp[(1) - (1)].dValue),false,true,false); 
        ;}
    break;

  case 59:

    { 
            int v = 0;
            ParserState* pp = static_cast<ParserState*>(parm);
            if (pp->floatvarTable.get((yyvsp[(1) - (1)].sValue), v))
                (yyval.varSpec) = new FloatVarSpec(Alias(v),false,true,false);
            else {
                pp->err << "Error: undefined identifier " << (yyvsp[(1) - (1)].sValue)
                        << " in line no. "
                        << yyget_lineno(pp->yyscanner) << std::endl;
                pp->hadError = true;
                (yyval.varSpec) = new FloatVarSpec(0.0,false,true,false);
            }
            free((yyvsp[(1) - (1)].sValue));
        ;}
    break;

  case 60:

    { 
            vector<int> v;
            ParserState* pp = static_cast<ParserState*>(parm);
            if (pp->floatvararrays.get((yyvsp[(1) - (4)].sValue), v)) {
                yyassert(pp,static_cast<unsigned int>((yyvsp[(3) - (4)].iValue)) > 0 && 
                                        static_cast<unsigned int>((yyvsp[(3) - (4)].iValue)) <= v.size(),
                                 "array access out of bounds");
                if (!pp->hadError)
                    (yyval.varSpec) = new FloatVarSpec(Alias(v[(yyvsp[(3) - (4)].iValue)-1]),false,true,false);
                else
                    (yyval.varSpec) = new FloatVarSpec(0.0,false,true,false);
            } else {
                pp->err << "Error: undefined array identifier " << (yyvsp[(1) - (4)].sValue)
                        << " in line no. "
                        << yyget_lineno(pp->yyscanner) << std::endl;
                pp->hadError = true;
                (yyval.varSpec) = new FloatVarSpec(0.0,false,true,false);
            }
            free((yyvsp[(1) - (4)].sValue));
        ;}
    break;

  case 61:

    { 
            (yyval.varSpecVec) = new vector<VarSpec*>(0); 
        ;}
    break;

  case 62:

    { 
            (yyval.varSpecVec) = (yyvsp[(1) - (2)].varSpecVec); 
        ;}
    break;

  case 63:

    {   
            (yyval.varSpecVec) = new vector<VarSpec*>(1); 
            (*(yyval.varSpecVec))[0] = (yyvsp[(1) - (1)].varSpec); 
        ;}
    break;

  case 64:

    { 
            (yyval.varSpecVec) = (yyvsp[(1) - (3)].varSpecVec); 
            (yyval.varSpecVec)->push_back((yyvsp[(3) - (3)].varSpec)); 
        ;}
    break;

  case 65:

    { 
            (yyval.varSpecVec) = (yyvsp[(2) - (3)].varSpecVec); 
        ;}
    break;

  case 66:

    { 
            (yyval.varSpec) = new BoolVarSpec((yyvsp[(1) - (1)].iValue),false,true,false); 
        ;}
    break;

  case 67:

    { 
            int v = 0;
            ParserState* pp = static_cast<ParserState*>(parm);
            if (pp->boolvarTable.get((yyvsp[(1) - (1)].sValue), v))
                (yyval.varSpec) = new BoolVarSpec(Alias(v),false,true,false);
            else {
                pp->err << "Error: undefined identifier " << (yyvsp[(1) - (1)].sValue)
                        << " in line no. "
                        << yyget_lineno(pp->yyscanner) << std::endl;
                pp->hadError = true;
                (yyval.varSpec) = new BoolVarSpec(false,false,true,false);
            }
            free((yyvsp[(1) - (1)].sValue));
        ;}
    break;

  case 68:

    { 
            vector<int> v;
            ParserState* pp = static_cast<ParserState*>(parm);
            if (pp->boolvararrays.get((yyvsp[(1) - (4)].sValue), v)) {
                yyassert(pp,static_cast<unsigned int>((yyvsp[(3) - (4)].iValue)) > 0 && 
                                        static_cast<unsigned int>((yyvsp[(3) - (4)].iValue)) <= v.size(),
                                 "array access out of bounds");
                if (!pp->hadError)
                    (yyval.varSpec) = new BoolVarSpec(Alias(v[(yyvsp[(3) - (4)].iValue)-1]),false,true,false);
                else
                    (yyval.varSpec) = new BoolVarSpec(false,false,true,false);
            } else {
                pp->err << "Error: undefined array identifier " << (yyvsp[(1) - (4)].sValue)
                        << " in line no. "
                        << yyget_lineno(pp->yyscanner) << std::endl;
                pp->hadError = true;
                (yyval.varSpec) = new BoolVarSpec(false,false,true,false);
            }
            free((yyvsp[(1) - (4)].sValue));
        ;}
    break;

  case 69:

    { 
            (yyval.varSpecVec) = new vector<VarSpec*>(0); 
        ;}
    break;

  case 70:

    { 
            (yyval.varSpecVec) = (yyvsp[(1) - (2)].varSpecVec); 
        ;}
    break;

  case 71:

    { 
            (yyval.varSpecVec) = new vector<VarSpec*>(1); 
            (*(yyval.varSpecVec))[0] = (yyvsp[(1) - (1)].varSpec); 
        ;}
    break;

  case 72:

    { 
            (yyval.varSpecVec) = (yyvsp[(1) - (3)].varSpecVec); 
            (yyval.varSpecVec)->push_back((yyvsp[(3) - (3)].varSpec)); 
        ;}
    break;

  case 73:

    { (yyval.varSpecVec) = (yyvsp[(2) - (3)].varSpecVec); ;}
    break;

  case 74:

    { 
            (yyval.varSpec) = new SetVarSpec(Option<AST::SetLit*>::some((yyvsp[(1) - (1)].setLit)),false,true,false); 
        ;}
    break;

  case 75:

    { 
            ParserState* pp = static_cast<ParserState*>(parm);
            int v = 0;
            if (pp->setvarTable.get((yyvsp[(1) - (1)].sValue), v))
                (yyval.varSpec) = new SetVarSpec(Alias(v),false,true,false);
            else {
                pp->err << "Error: undefined identifier " << (yyvsp[(1) - (1)].sValue)
                        << " in line no. "
                        << yyget_lineno(pp->yyscanner) << std::endl;
                pp->hadError = true;
                (yyval.varSpec) = new SetVarSpec(Alias(0),false,true,false);
            }
            free((yyvsp[(1) - (1)].sValue));
        ;}
    break;

  case 76:

    { 
            vector<int> v;
            ParserState* pp = static_cast<ParserState*>(parm);
            if (pp->setvararrays.get((yyvsp[(1) - (4)].sValue), v)) {
                yyassert(pp,static_cast<unsigned int>((yyvsp[(3) - (4)].iValue)) > 0 && 
                                        static_cast<unsigned int>((yyvsp[(3) - (4)].iValue)) <= v.size(),
                                 "array access out of bounds");
                if (!pp->hadError)
                    (yyval.varSpec) = new SetVarSpec(Alias(v[(yyvsp[(3) - (4)].iValue)-1]),false,true,false);
                else
                    (yyval.varSpec) = new SetVarSpec(Alias(0),false,true,false);
            } else {
                pp->err << "Error: undefined array identifier " << (yyvsp[(1) - (4)].sValue)
                        << " in line no. "
                        << yyget_lineno(pp->yyscanner) << std::endl;
                pp->hadError = true;
                (yyval.varSpec) = new SetVarSpec(Alias(0),false,true,false);
            }
            free((yyvsp[(1) - (4)].sValue));
        ;}
    break;

  case 77:

    { 
            (yyval.varSpecVec) = new vector<VarSpec*>(0); 
        ;}
    break;

  case 78:

    { 
            (yyval.varSpecVec) = (yyvsp[(1) - (2)].varSpecVec); 
        ;}
    break;

  case 79:

    { 
            (yyval.varSpecVec) = new vector<VarSpec*>(1); 
            (*(yyval.varSpecVec))[0] = (yyvsp[(1) - (1)].varSpec); 
        ;}
    break;

  case 80:

    { 
            (yyval.varSpecVec) = (yyvsp[(1) - (3)].varSpecVec); 
            (yyval.varSpecVec)->push_back((yyvsp[(3) - (3)].varSpec)); 
        ;}
    break;

  case 81:

    { 
            (yyval.varSpecVec) = (yyvsp[(2) - (3)].varSpecVec); 
        ;}
    break;

  case 82:

    { 
            (yyval.oVarSpecVec) = Option<vector<VarSpec*>* >::none(); 
        ;}
    break;

  case 83:

    { 
            (yyval.oVarSpecVec) = Option<vector<VarSpec*>* >::some((yyvsp[(2) - (2)].varSpecVec)); 
        ;}
    break;

  case 84:

    { 
            (yyval.oVarSpecVec) = Option<vector<VarSpec*>* >::none(); 
        ;}
    break;

  case 85:

    { 
            (yyval.oVarSpecVec) = Option<vector<VarSpec*>* >::some((yyvsp[(2) - (2)].varSpecVec)); 
        ;}
    break;

  case 86:

    { 
            (yyval.oVarSpecVec) = Option<vector<VarSpec*>* >::none(); 
        ;}
    break;

  case 87:

    { 
            (yyval.oVarSpecVec) = Option<vector<VarSpec*>* >::some((yyvsp[(2) - (2)].varSpecVec)); 
        ;}
    break;

  case 88:

    { 
            (yyval.oVarSpecVec) = Option<vector<VarSpec*>* >::none(); 
        ;}
    break;

  case 89:

    { 
            (yyval.oVarSpecVec) = Option<vector<VarSpec*>* >::some((yyvsp[(2) - (2)].varSpecVec)); 
        ;}
    break;

  case 90:

    { 
            ParserState *pp = static_cast<ParserState*>(parm);
#if EXPOSE_INT_LITS
            pp->domainConstraints2.push_back(std::pair<ConExpr*, AST::Node*>(new ConExpr((yyvsp[(2) - (6)].sValue), (yyvsp[(4) - (6)].argVec)), (yyvsp[(6) - (6)].argVec)));
#else
            ConExpr c((yyvsp[(2) - (6)].sValue), (yyvsp[(4) - (6)].argVec));
            if (!pp->hadError) {
                try {
                    pp->fg->postConstraint(c, (yyvsp[(6) - (6)].argVec));
                } catch (FlatZinc::Error& e) {
                    yyerror(pp, e.toString().c_str());
                }
            }
            delete (yyvsp[(6) - (6)].argVec);
#endif
            free((yyvsp[(2) - (6)].sValue));
        ;}
    break;

  case 91:

    {
            ParserState *pp = static_cast<ParserState*>(parm);
            AST::Array* args = new AST::Array(2);
            args->a[0] = getVarRefArg(pp,(yyvsp[(2) - (3)].sValue));
            args->a[1] = new AST::BoolLit(true);
#if EXPOSE_INT_LITS
            pp->domainConstraints2.push_back(std::pair<ConExpr*, AST::Node*>(new ConExpr("bool_eq", args), (yyvsp[(3) - (3)].argVec)));
#else
            ConExpr c("bool_eq", args);
            if (!pp->hadError) {
                try {
                    pp->fg->postConstraint(c, (yyvsp[(3) - (3)].argVec));
                } catch (FlatZinc::Error& e) {
                    yyerror(pp, e.toString().c_str());
                }
            }
            delete (yyvsp[(3) - (3)].argVec);
#endif
            free((yyvsp[(2) - (3)].sValue));
        ;}
    break;

  case 92:

    { 
            ParserState *pp = static_cast<ParserState*>(parm);
            AST::Array* args = new AST::Array(2);
            args->a[0] = getArrayElement(pp,(yyvsp[(2) - (6)].sValue),(yyvsp[(4) - (6)].iValue));
            args->a[1] = new AST::BoolLit(true);
#if EXPOSE_INT_LITS
            pp->domainConstraints2.push_back(std::pair<ConExpr*, AST::Node*>(new ConExpr("bool_eq", args), (yyvsp[(6) - (6)].argVec)));
#else
            ConExpr c("bool_eq", args);
            if (!pp->hadError) {
                try {
                    pp->fg->postConstraint(c, (yyvsp[(6) - (6)].argVec));
                } catch (FlatZinc::Error& e) {
                    yyerror(pp, e.toString().c_str());
                }
            }
            delete (yyvsp[(6) - (6)].argVec);
#endif
            free((yyvsp[(2) - (6)].sValue));
        ;}
    break;

  case 93:

    { 
            ParserState *pp = static_cast<ParserState*>(parm);
            if (!pp->hadError) {
                pp->fg->solve((yyvsp[(2) - (3)].argVec));
            }
            delete (yyvsp[(2) - (3)].argVec);
        ;}
    break;

  case 94:

    { 
            ParserState *pp = static_cast<ParserState*>(parm);
            if (!pp->hadError) {
                if ((yyvsp[(3) - (4)].bValue))
                    pp->fg->minimize((yyvsp[(4) - (4)].iValue),(yyvsp[(2) - (4)].argVec));
                else
                    pp->fg->maximize((yyvsp[(4) - (4)].iValue),(yyvsp[(2) - (4)].argVec));
            }
            delete (yyvsp[(2) - (4)].argVec);
        ;}
    break;

  case 95:

    { 
            (yyval.oSet) = Option<AST::SetLit* >::none(); 
        ;}
    break;

  case 96:

    { 
            (yyval.oSet) = Option<AST::SetLit* >::some(new AST::SetLit(*(yyvsp[(2) - (3)].setValue))); 
        ;}
    break;

  case 97:

    { 
            (yyval.oSet) = Option<AST::SetLit* >::some(new AST::SetLit((yyvsp[(1) - (3)].iValue), (yyvsp[(3) - (3)].iValue)));
        ;}
    break;

  case 98:

    { 
            (yyval.oSet) = Option<AST::SetLit* >::none(); 
        ;}
    break;

  case 99:

    { 
            bool haveTrue = false;
            bool haveFalse = false;
            for (int i = (yyvsp[(2) - (4)].setValue)->size(); i--;) {
                haveTrue |= ((*(yyvsp[(2) - (4)].setValue))[i] == 1);
                haveFalse |= ((*(yyvsp[(2) - (4)].setValue))[i] == 0);
            }
            delete (yyvsp[(2) - (4)].setValue);
            (yyval.oSet) = Option<AST::SetLit* >::some(
                new AST::SetLit(!haveFalse,haveTrue));
        ;}
    break;

  case 102:

    { 
            (yyval.setLit) = new AST::SetLit(*(yyvsp[(2) - (3)].setValue)); 
        ;}
    break;

  case 103:

    { 
            (yyval.setLit) = new AST::SetLit((yyvsp[(1) - (3)].iValue), (yyvsp[(3) - (3)].iValue)); 
        ;}
    break;

  case 104:

    { 
            (yyval.setValue) = new vector<int>(0); 
        ;}
    break;

  case 105:

    { 
            (yyval.setValue) = (yyvsp[(1) - (2)].setValue); 
        ;}
    break;

  case 106:

    { 
            (yyval.setValue) = new vector<int>(1); 
            (*(yyval.setValue))[0] = (yyvsp[(1) - (1)].iValue); 
        ;}
    break;

  case 107:

    { 
            (yyval.setValue) = (yyvsp[(1) - (3)].setValue); 
            (yyval.setValue)->push_back((yyvsp[(3) - (3)].iValue)); 
        ;}
    break;

  case 108:

    { 
            (yyval.setValue) = new vector<int>(0); 
        ;}
    break;

  case 109:

    { 
            (yyval.setValue) = (yyvsp[(1) - (2)].setValue); 
        ;}
    break;

  case 110:

    { 
            (yyval.setValue) = new vector<int>(1); 
            (*(yyval.setValue))[0] = (yyvsp[(1) - (1)].iValue); 
        ;}
    break;

  case 111:

    { 
            (yyval.setValue) = (yyvsp[(1) - (3)].setValue); 
            (yyval.setValue)->push_back((yyvsp[(3) - (3)].iValue)); 
        ;}
    break;

  case 112:

    { 
            (yyval.floatSetValue) = new vector<double>(0); 
        ;}
    break;

  case 113:

    { 
            (yyval.floatSetValue) = (yyvsp[(1) - (2)].floatSetValue); 
        ;}
    break;

  case 114:

    {
            (yyval.floatSetValue) = new vector<double>(1); 
            (*(yyval.floatSetValue))[0] = (yyvsp[(1) - (1)].dValue); 
        ;}
    break;

  case 115:

    { 
            (yyval.floatSetValue) = (yyvsp[(1) - (3)].floatSetValue); 
            (yyval.floatSetValue)->push_back((yyvsp[(3) - (3)].dValue)); 
        ;}
    break;

  case 116:

    { 
            (yyval.setValueList) = new vector<AST::SetLit>(0); 
        ;}
    break;

  case 117:

    { 
            (yyval.setValueList) = (yyvsp[(1) - (2)].setValueList); 
        ;}
    break;

  case 118:

    { 
            (yyval.setValueList) = new vector<AST::SetLit>(1); 
            (*(yyval.setValueList))[0] = *(yyvsp[(1) - (1)].setLit); 
            delete (yyvsp[(1) - (1)].setLit); 
        ;}
    break;

  case 119:

    { 
            (yyval.setValueList) = (yyvsp[(1) - (3)].setValueList); 
            (yyval.setValueList)->push_back(*(yyvsp[(3) - (3)].setLit)); 
            delete (yyvsp[(3) - (3)].setLit); 
        ;}
    break;

  case 120:

    { 
            (yyval.argVec) = new AST::Array((yyvsp[(1) - (1)].arg)); 
        ;}
    break;

  case 121:

    { 
            (yyval.argVec) = (yyvsp[(1) - (3)].argVec); 
            (yyval.argVec)->append((yyvsp[(3) - (3)].arg)); 
        ;}
    break;

  case 122:

    { 
            (yyval.arg) = (yyvsp[(1) - (1)].arg); 
        ;}
    break;

  case 123:

    { 
            (yyval.arg) = (yyvsp[(2) - (3)].argVec); 
        ;}
    break;

  case 124:

    { 
            (yyval.oArg) = Option<AST::Node*>::none(); 
        ;}
    break;

  case 125:

    { 
            (yyval.oArg) = Option<AST::Node*>::some((yyvsp[(2) - (2)].arg)); 
        ;}
    break;

  case 126:

    { 
            (yyval.arg) = new AST::BoolLit((yyvsp[(1) - (1)].iValue)); 
        ;}
    break;

  case 127:

    { 
            (yyval.arg) = new AST::IntLit((yyvsp[(1) - (1)].iValue)); 
        ;}
    break;

  case 128:

    { 
            (yyval.arg) = new AST::FloatLit((yyvsp[(1) - (1)].dValue)); 
        ;}
    break;

  case 129:

    { 
            (yyval.arg) = (yyvsp[(1) - (1)].setLit); 
        ;}
    break;

  case 130:

    { 
            vector<int> as;
            ParserState* pp = static_cast<ParserState*>(parm);
            if (pp->intvararrays.get((yyvsp[(1) - (1)].sValue), as)) {
                AST::Array *ia = new AST::Array(as.size());
                for (int i = as.size(); i--;)
                    ia->a[i] = new AST::IntVar(as[i]);
                (yyval.arg) = ia;
            } else if (pp->boolvararrays.get((yyvsp[(1) - (1)].sValue), as)) {
                AST::Array *ia = new AST::Array(as.size());
                for (int i = as.size(); i--;)
                    ia->a[i] = new AST::BoolVar(as[i]);
                (yyval.arg) = ia;
            } else if (pp->setvararrays.get((yyvsp[(1) - (1)].sValue), as)) {
                AST::Array *ia = new AST::Array(as.size());
                for (int i = as.size(); i--;)
                    ia->a[i] = new AST::SetVar(as[i]);
                (yyval.arg) = ia;
            } else {
                std::vector<int> is;
                std::vector<AST::SetLit> isS;
                int ival = 0;
                bool bval = false;
                if (pp->intvalarrays.get((yyvsp[(1) - (1)].sValue), is)) {
                    AST::Array *v = new AST::Array(is.size());
                    for (int i = is.size(); i--;)
                        v->a[i] = new AST::IntLit(is[i]);
                    (yyval.arg) = v;
                } else if (pp->boolvalarrays.get((yyvsp[(1) - (1)].sValue), is)) {
                    AST::Array *v = new AST::Array(is.size());
                    for (int i = is.size(); i--;)
                        v->a[i] = new AST::BoolLit(is[i]);
                    (yyval.arg) = v;
                } else if (pp->setvalarrays.get((yyvsp[(1) - (1)].sValue), isS)) {
                    AST::Array *v = new AST::Array(isS.size());
                    for (int i = isS.size(); i--;)
                        v->a[i] = new AST::SetLit(isS[i]);
                    (yyval.arg) = v;                      
                } else if (pp->intvals.get((yyvsp[(1) - (1)].sValue), ival)) {
                    (yyval.arg) = new AST::IntLit(ival);
                } else if (pp->boolvals.get((yyvsp[(1) - (1)].sValue), bval)) {
                    (yyval.arg) = new AST::BoolLit(bval);
                } else {
                    (yyval.arg) = getVarRefArg(pp,(yyvsp[(1) - (1)].sValue));
                }
            }
            free((yyvsp[(1) - (1)].sValue));
        ;}
    break;

  case 131:

    { 
            ParserState* pp = static_cast<ParserState*>(parm);
            int i = -1;
            yyassert(pp, (yyvsp[(3) - (4)].arg)->isInt(i), "Non-integer array index.");
            if (!pp->hadError)
                (yyval.arg) = getArrayElement(static_cast<ParserState*>(parm),(yyvsp[(1) - (4)].sValue),i);
            else
                (yyval.arg) = new AST::IntLit(0); // keep things consistent
            free((yyvsp[(1) - (4)].sValue));
        ;}
    break;

  case 132:

    { 
            (yyval.argVec) = new AST::Array(0); 
        ;}
    break;

  case 133:

    { 
            (yyval.argVec) = (yyvsp[(1) - (2)].argVec); 
        ;}
    break;

  case 134:

    { 
            (yyval.argVec) = new AST::Array((yyvsp[(1) - (1)].arg)); 
        ;}
    break;

  case 135:

    { 
            (yyval.argVec) = (yyvsp[(1) - (3)].argVec); 
            (yyval.argVec)->append((yyvsp[(3) - (3)].arg)); 
        ;}
    break;

  case 136:

    {
            ParserState *pp = static_cast<ParserState*>(parm);
            // Create a new variable in the parser and append at the end
            const int i = pp->intvars.size();
            const std::string objname = "X_INTRODUCED_CHUFFEDOBJ";
            pp->intvarTable.put(objname, i);
            pp->intvars.push_back(varspec(objname,
                new IntVarSpec((yyvsp[(1) - (1)].iValue),false,true,false)));
            if (pp->fg != NULL) {
                // Add a new IntVar to the FlatZincSpace if it was already created
                try {
                    pp->fg->newIntVar(static_cast<IntVarSpec*>(pp->intvars[i].second));
                    IntVar* newiv = pp->fg->iv[pp->fg->intVarCount-1];
                    intVarString.insert(std::pair<IntVar*, std::string>(newiv, pp->intvars[i].first));
                } catch (FlatZinc::Error& e) {
                    yyerror(pp, e.toString().c_str());
                }
            }
            (yyval.iValue) = i;
        ;}
    break;

  case 137:

    { 
            ParserState *pp = static_cast<ParserState*>(parm);
            int tmp = -1;
            // Check whether the Objective variable is an integer constant
            if (pp->intvals.get((yyvsp[(1) - (1)].sValue), tmp) && !pp->intvarTable.get((yyvsp[(1) - (1)].sValue), (yyval.iValue))) {
                // Create a new variable in the parser and append at the end
                const int i = pp->intvars.size();
                pp->intvarTable.put((yyvsp[(1) - (1)].sValue), i);
                pp->intvars.push_back(varspec((yyvsp[(1) - (1)].sValue),
                    new IntVarSpec(tmp,false,true,false)));
                if (pp->fg != NULL) {
                    // Add a new IntVar to the FlatZincSpace if it was already created
                    try {
                        pp->fg->newIntVar(static_cast<IntVarSpec*>(pp->intvars[i].second));
                        IntVar* newiv = pp->fg->iv[pp->fg->intVarCount-1];
                        intVarString.insert(std::pair<IntVar*, std::string>(newiv, pp->intvars[i].first));
                    } catch (FlatZinc::Error& e) {
                        yyerror(pp, e.toString().c_str());
                    }
                }
            }
            if (!pp->intvarTable.get((yyvsp[(1) - (1)].sValue), (yyval.iValue))) {
                pp->err << "Error: unknown integer variable " << (yyvsp[(1) - (1)].sValue)
                        << " in line no. "
                        << yyget_lineno(pp->yyscanner) << std::endl;
                pp->hadError = true;
            }
            free((yyvsp[(1) - (1)].sValue));
        ;}
    break;

  case 138:

    {
            vector<int> tmp;
            ParserState *pp = static_cast<ParserState*>(parm);
            if (!pp->intvararrays.get((yyvsp[(1) - (4)].sValue), tmp)) {
                pp->err << "Error: unknown integer variable array " << (yyvsp[(1) - (4)].sValue)
                        << " in line no. "
                        << yyget_lineno(pp->yyscanner) << std::endl;
                pp->hadError = true;
            }
            if ((yyvsp[(3) - (4)].iValue) == 0 || static_cast<unsigned int>((yyvsp[(3) - (4)].iValue)) > tmp.size()) {
                pp->err << "Error: array index out of bounds for array " << (yyvsp[(1) - (4)].sValue)
                        << " in line no. "
                        << yyget_lineno(pp->yyscanner) << std::endl;
                pp->hadError = true;
            } else {
                (yyval.iValue) = tmp[(yyvsp[(3) - (4)].iValue)-1];
            }
            free((yyvsp[(1) - (4)].sValue));
        ;}
    break;

  case 141:

    { 
            (yyval.argVec) = NULL; 
        ;}
    break;

  case 142:

    { 
            (yyval.argVec) = (yyvsp[(1) - (1)].argVec); 
        ;}
    break;

  case 143:

    { 
            (yyval.argVec) = new AST::Array((yyvsp[(2) - (2)].arg)); 
        ;}
    break;

  case 144:

    { 
            (yyval.argVec) = (yyvsp[(1) - (3)].argVec); 
            (yyval.argVec)->append((yyvsp[(3) - (3)].arg)); 
        ;}
    break;

  case 145:

    { 
            (yyval.arg) = new AST::Call((yyvsp[(1) - (4)].sValue), AST::extractSingleton((yyvsp[(3) - (4)].arg))); 
            free((yyvsp[(1) - (4)].sValue));
        ;}
    break;

  case 146:

    { 
            (yyval.arg) = (yyvsp[(1) - (1)].arg); 
        ;}
    break;

  case 147:

    { 
            (yyval.arg) = new AST::Array((yyvsp[(1) - (1)].arg)); 
        ;}
    break;

  case 148:

    { 
            (yyval.arg) = (yyvsp[(1) - (3)].arg); 
            (yyval.arg)->append((yyvsp[(3) - (3)].arg)); 
        ;}
    break;

  case 149:

    { 
            (yyval.arg) = (yyvsp[(1) - (1)].arg); 
        ;}
    break;

  case 150:

    { 
            (yyval.arg) = (yyvsp[(2) - (3)].arg); 
        ;}
    break;

  case 151:

    { 
            (yyval.arg) = new AST::BoolLit((yyvsp[(1) - (1)].iValue)); 
        ;}
    break;

  case 152:

    { 
            (yyval.arg) = new AST::IntLit((yyvsp[(1) - (1)].iValue)); 
        ;}
    break;

  case 153:

    { 
            (yyval.arg) = new AST::FloatLit((yyvsp[(1) - (1)].dValue)); 
        ;}
    break;

  case 154:

    { 
            (yyval.arg) = (yyvsp[(1) - (1)].setLit); 
        ;}
    break;

  case 155:

    { 
            vector<int> as;
            ParserState* pp = static_cast<ParserState*>(parm);
            if (pp->intvararrays.get((yyvsp[(1) - (1)].sValue), as)) {
                AST::Array *ia = new AST::Array(as.size());
                for (int i = as.size(); i--;)
                    ia->a[i] = new AST::IntVar(as[i]);
                (yyval.arg) = ia;
            } else if (pp->boolvararrays.get((yyvsp[(1) - (1)].sValue), as)) {
                AST::Array *ia = new AST::Array(as.size());
                for (int i = as.size(); i--;)
                    ia->a[i] = new AST::BoolVar(as[i]);
                (yyval.arg) = ia;
            } else if (pp->setvararrays.get((yyvsp[(1) - (1)].sValue), as)) {
                AST::Array *ia = new AST::Array(as.size());
                for (int i = as.size(); i--;)
                    ia->a[i] = new AST::SetVar(as[i]);
                (yyval.arg) = ia;
            } else {
                std::vector<int> is;
                int ival = 0;
                bool bval = false;
                if (pp->intvalarrays.get((yyvsp[(1) - (1)].sValue), is)) {
                    AST::Array *v = new AST::Array(is.size());
                    for (int i = is.size(); i--;)
                        v->a[i] = new AST::IntLit(is[i]);
                    (yyval.arg) = v;
                } else if (pp->boolvalarrays.get((yyvsp[(1) - (1)].sValue), is)) {
                    AST::Array *v = new AST::Array(is.size());
                    for (int i = is.size(); i--;)
                        v->a[i] = new AST::BoolLit(is[i]);
                    (yyval.arg) = v;
                } else if (pp->intvals.get((yyvsp[(1) - (1)].sValue), ival)) {
                    (yyval.arg) = new AST::IntLit(ival);
                } else if (pp->boolvals.get((yyvsp[(1) - (1)].sValue), bval)) {
                    (yyval.arg) = new AST::BoolLit(bval);
                } else {
                    (yyval.arg) = getVarRefArg(pp,(yyvsp[(1) - (1)].sValue),true);
                }
            }
            free((yyvsp[(1) - (1)].sValue));
        ;}
    break;

  case 156:

    { 
            ParserState* pp = static_cast<ParserState*>(parm);
            int i = -1;
            yyassert(pp, (yyvsp[(3) - (4)].arg)->isInt(i), "Non-integer array index.");
            if (!pp->hadError)
                (yyval.arg) = getArrayElement(static_cast<ParserState*>(parm),(yyvsp[(1) - (4)].sValue),i);
            else
                (yyval.arg) = new AST::IntLit(0); // keep things consistent
            free((yyvsp[(1) - (4)].sValue));
        ;}
    break;

  case 157:

    {
            (yyval.arg) = new AST::String((yyvsp[(1) - (1)].sValue));
            free((yyvsp[(1) - (1)].sValue));
        ;}
    break;


/* Line 1267 of yacc.c.  */

      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (parm, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (parm, yymsg);
	  }
	else
	  {
	    yyerror (parm, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, parm);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, parm);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (parm, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, parm);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, parm);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



