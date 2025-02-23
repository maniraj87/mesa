// DriConf options supported by all Gallium DRI drivers.
DRI_CONF_SECTION_PERFORMANCE
   DRI_CONF_MESA_GLTHREAD(false)
   DRI_CONF_MESA_NO_ERROR(false)
DRI_CONF_SECTION_END

DRI_CONF_SECTION_QUALITY
   DRI_CONF_PP_CELSHADE(0)
   DRI_CONF_PP_NORED(0)
   DRI_CONF_PP_NOGREEN(0)
   DRI_CONF_PP_NOBLUE(0)
   DRI_CONF_PP_JIMENEZMLAA(0, 0, 32)
   DRI_CONF_PP_JIMENEZMLAA_COLOR(0, 0, 32)
DRI_CONF_SECTION_END

DRI_CONF_SECTION_DEBUG
   DRI_CONF_FORCE_GLSL_EXTENSIONS_WARN(false)
   DRI_CONF_DISABLE_GLSL_LINE_CONTINUATIONS(false)
   DRI_CONF_DISABLE_BLEND_FUNC_EXTENDED(false)
   DRI_CONF_DISABLE_ARB_GPU_SHADER5(false)
   DRI_CONF_FORCE_GLSL_VERSION(0)
   DRI_CONF_ALLOW_EXTRA_PP_TOKENS(false)
   DRI_CONF_ALLOW_GLSL_EXTENSION_DIRECTIVE_MIDSHADER(false)
   DRI_CONF_ALLOW_GLSL_120_SUBSET_IN_110(false)
   DRI_CONF_ALLOW_GLSL_BUILTIN_CONST_EXPRESSION(false)
   DRI_CONF_ALLOW_GLSL_RELAXED_ES(false)
   DRI_CONF_ALLOW_GLSL_BUILTIN_VARIABLE_REDECLARATION(false)
   DRI_CONF_ALLOW_GLSL_CROSS_STAGE_INTERPOLATION_MISMATCH(false)
   DRI_CONF_ALLOW_HIGHER_COMPAT_VERSION(false)
   DRI_CONF_FORCE_GLSL_ABS_SQRT(false)
   DRI_CONF_GLSL_CORRECT_DERIVATIVES_AFTER_DISCARD(false)
   DRI_CONF_GLSL_IGNORE_WRITE_TO_READONLY_VAR(false)
   DRI_CONF_ALLOW_DRAW_OUT_OF_ORDER(false)
   DRI_CONF_FORCE_COMPAT_PROFILE(false)
   DRI_CONF_FORCE_GL_NAMES_REUSE(false)
   DRI_CONF_TRANSCODE_ETC(false)
   DRI_CONF_TRANSCODE_ASTC(false)
   DRI_CONF_FORCE_GL_VENDOR()
   DRI_CONF_FORCE_GL_RENDERER()
   DRI_CONF_OVERRIDE_VRAM_SIZE()
   DRI_CONF_GLX_EXTENSION_OVERRIDE()
   DRI_CONF_INDIRECT_GL_EXTENSION_OVERRIDE()
   DRI_CONF_DISABLE_PROTECTED_CONTENT_CHECK(false)
   DRI_CONF_IGNORE_MAP_UNSYNCHRONIZED(false)
DRI_CONF_SECTION_END

DRI_CONF_SECTION_MISCELLANEOUS
   DRI_CONF_ALWAYS_HAVE_DEPTH_BUFFER(false)
   DRI_CONF_GLSL_ZERO_INIT(false)
   DRI_CONF_VS_POSITION_ALWAYS_INVARIANT(false)
   DRI_CONF_VS_POSITION_ALWAYS_PRECISE(false)
   DRI_CONF_ALLOW_RGB10_CONFIGS(true)
   DRI_CONF_ALLOW_FP16_CONFIGS(false)
   DRI_CONF_FORCE_INTEGER_TEX_NEAREST(false)
DRI_CONF_SECTION_END
