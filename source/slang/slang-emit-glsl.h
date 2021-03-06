// slang-emit-glsl.h
#ifndef SLANG_EMIT_GLSL_H
#define SLANG_EMIT_GLSL_H

#include "slang-emit-c-like.h"

#include "slang-glsl-extension-tracker.h"

namespace Slang
{

class GLSLSourceEmitter : public CLikeSourceEmitter
{
public:
    typedef CLikeSourceEmitter Super;

    GLSLSourceEmitter(const Desc& desc) :
        Super(desc)
    {
        m_glslExtensionTracker = new GLSLExtensionTracker;
    }

    virtual RefObject* getExtensionTracker() SLANG_OVERRIDE { return m_glslExtensionTracker; }

protected:

    virtual void emitParameterGroupImpl(IRGlobalParam* varDecl, IRUniformParameterGroupType* type) SLANG_OVERRIDE;
    virtual void emitEntryPointAttributesImpl(IRFunc* irFunc, IREntryPointDecoration* entryPointDecor) SLANG_OVERRIDE;
    virtual void emitImageFormatModifierImpl(IRInst* varDecl, IRType* varType) SLANG_OVERRIDE;
    virtual void emitLayoutQualifiersImpl(IRVarLayout* layout) SLANG_OVERRIDE;
    
    virtual void emitTextureOrTextureSamplerTypeImpl(IRTextureTypeBase*  type, char const* baseName) SLANG_OVERRIDE { _emitGLSLTextureOrTextureSamplerType(type, baseName); }

    virtual void emitPreprocessorDirectivesImpl() SLANG_OVERRIDE;
    virtual void emitLayoutDirectivesImpl(TargetRequest* targetReq) SLANG_OVERRIDE;
    virtual void emitRateQualifiersImpl(IRRate* rate) SLANG_OVERRIDE;
    virtual void emitInterpolationModifiersImpl(IRInst* varInst, IRType* valueType, IRVarLayout* layout) SLANG_OVERRIDE;
    virtual void emitSimpleTypeImpl(IRType* type) SLANG_OVERRIDE;
    virtual void emitVectorTypeNameImpl(IRType* elementType, IRIntegerValue elementCount) SLANG_OVERRIDE;
    virtual void emitVarDecorationsImpl(IRInst* varDecl) SLANG_OVERRIDE;
    virtual void emitMatrixLayoutModifiersImpl(IRVarLayout* layout) SLANG_OVERRIDE;

    virtual void handleCallExprDecorationsImpl(IRInst* funcValue) SLANG_OVERRIDE;

    virtual bool tryEmitGlobalParamImpl(IRGlobalParam* varDecl, IRType* varType) SLANG_OVERRIDE;
    virtual bool tryEmitInstExprImpl(IRInst* inst, const EmitOpInfo& inOuterPrec) SLANG_OVERRIDE;

    virtual void emitSimpleValueImpl(IRInst* inst) SLANG_OVERRIDE;
    virtual void emitLoopControlDecorationImpl(IRLoopControlDecoration* decl) SLANG_OVERRIDE;

    void _emitGLSLTextureOrTextureSamplerType(IRTextureTypeBase* type, char const* baseName);
    void _emitGLSLStructuredBuffer(IRGlobalParam* varDecl, IRHLSLStructuredBufferTypeBase* structuredBufferType);

    void _emitGLSLByteAddressBuffer(IRGlobalParam* varDecl, IRByteAddressBufferTypeBase* byteAddressBufferType);
    void _emitGLSLParameterGroup(IRGlobalParam* varDecl, IRUniformParameterGroupType* type);

    void _emitGLSLImageFormatModifier(IRInst* var, IRTextureType* resourceType);

    void _emitGLSLLayoutQualifiers(IRVarLayout* layout, EmitVarChain* inChain, LayoutResourceKind filter = LayoutResourceKind::None);
    bool _emitGLSLLayoutQualifier(LayoutResourceKind kind, EmitVarChain* chain);

    void _emitGLSLTypePrefix(IRType* type, bool promoteHalfToFloat = false);

    void _requireGLSLExtension(const UnownedStringSlice& name);

    void _requireGLSLVersion(ProfileVersion version);
    void _requireGLSLVersion(int version);
    void _requireSPIRVVersion(const SemanticVersion& version);

        // Emit the `flat` qualifier if the underlying type
        // of the variable is an integer type.
    void _maybeEmitGLSLFlatModifier(IRType* valueType);

    void _requireBaseType(BaseType baseType);

    void _maybeEmitGLSLCast(IRType* castType, IRInst* inst);


    RefPtr<GLSLExtensionTracker> m_glslExtensionTracker;
};

}
#endif
