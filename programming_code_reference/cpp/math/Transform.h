#ifndef DDD_TRANSFORM_H_
#define DDD_TRANSFORM_H_

#include "reals.h"

namespace ddd {
	

enum TRANSFORM_FLAG_ENUM {
	T_DIRTY				= 0x00000001,	//track wheather the matrix have been concatenated
	T_STATIC			= 0x00000002,	//track to see if is a static transform, no update is needed throughout
	T_YET_TOUPDATE= 0x00000004,	//track wheather world coordinates have been updated, only applies to child transform
	T_ISBONE			= 0x00000008	//track wheather if is a bone object, internal use only
};

class Transform {
public:
	Transform	() noexcept;
	Transform	(const ddd::Vector3& position_, const ddd::Quaternion& quaternion_, const ddd::Vector3& scale_) noexcept;
	~Transform	() = default;
	
	// __________ static
	static Transform Identity;

	// ____________________________________________________________ setters
	void SetFacingVector		(const ddd::Vector3& zfacing);
	void SetAsBoneObject		(bool isBoneObject_);
	void SetStatic				(bool static_);
	void SetWorldFromMatrix		(const ddd::Matrix44& mat);
	void SetLocalFromMatrix		(const ddd::Matrix44& mat);

	// ____________________________________________________________ World
	void SetPosition			(float x_);
	void SetPosition			(float x_, float y_);
	void SetPosition			(float x_, float y_ , float z_);
	void SetPosition			(const ddd::Vector3& position_);
	void SetRotation			(float x_);
	void SetRotation			(float x_, float y_);
	void SetRotation			(float x_, float y_, float z_);
	void SetRotation			(const ddd::Vector3& eular_);
	void SetRotation			(const ddd::Quaternion& rotation_);
	void SetScale				(float x_);
	void SetScale				(float x_, float y_);
	void SetScale				(float x_, float y_ , float z_);
	void SetScale				(const ddd::Vector3& scale_);
	void SetUniformWorldScale2D	(float xy_);
	void SetUniformWorldScale3D	(float xyz_);

	// ____________________________________________________________ Local
	void SetLocalPosition		(float x_);
	void SetLocalPosition		(float x_, float y_);
	void SetLocalPosition		(float x_, float y_, float z_);
	void SetLocalPosition		(const ddd::Vector3& position_);
	void SetLocalRotation		(float x_);
	void SetLocalRotation		(float x_, float y_);
	void SetLocalRotation		(float x_, float y_, float z_);
	void SetLocalRotation		(const ddd::Vector3& localEular__);
	void SetLocalRotation		(const ddd::Quaternion& rotation_);
	void SetLocalScale			(float x_);
	void SetLocalScale			(float x_, float y_);
	void SetLocalScale			(float x_, float y_, float z_);
	void SetLocalScale			(const ddd::Vector3& scale_);
	void SetUniformLocalScale2D	(float xy_);
	void SetUniformLocalScale3D	(float xyz_);

	// ____________________________________________________________ world
	void Translate			(float x_, float y_ = 0.0f, float z_ = 0.0f);
	void Translate			(const ddd::Vector3& translate_);
	void Rotate				(float x_, float y_ = 0.0f, float z_ = 0.0f);
	void Rotate				(const ddd::Vector3& eular_);
	void Rotate				(const ddd::Quaternion& rotation_);
	void Scale				(float x_, float y_ = 0.0f, float z_ = 0.0f);
	void Scale				(const ddd::Vector3& scaling_);
	void ScaleMultiply		(float x_, float y_ = 0.0f, float z_ = 0.0f);
	void ScaleMultiply		(const ddd::Vector3& scaling_);
	// ____________________________________________________________ local
	void LocalTranslate		(float x_, float y_ = 0.0f, float z_ = 0.0f);
	void LocalTranslate		(const ddd::Vector3& translate_);
	void LocalRotate		(float x_, float y_ = 0.0f, float z_ = 0.0f);
	void LocalRotate		(const ddd::Vector3& eular_);
	void LocalRotate		(const ddd::Quaternion& rotation_);
	void LocalScale			(float x_, float y_ = 0.0f, float z_ = 0.0f);
	void LocalScale			(const ddd::Vector3& scaling_);
	void LocalScaleMultiply	(float x_, float y_ = 0.0f, float z_ = 0.0f);
	void LocalScaleMultiply	(const ddd::Vector3& scaling_);

	// ____________________________________________________________ getters
	Transform			GetConcatTransform	() const;
	Transform			GetInverse			() const;
	const ddd::Matrix44&	GetMatrix			();
	ddd::Matrix44		GetLocalMatrix		() const;
	const ddd::Matrix44&	GetWorldMatrix		() const;
	bool				HasUpdated			() const;
	bool				IsBone				() const;
	bool				IsStatic			() const;
	ddd::Vector3			Forward				() const;
	ddd::Vector3			Up					() const;
	ddd::Vector3			Right				() const;

	ddd::Vector3			GetWorldPosition	() const;
	ddd::Quaternion		GetWorldRotation	() const;
	ddd::Vector3			GetWorldScale		() const;

	//etc function
	void Attach						(Transform* parent);	//attach to a parent transform
	void Detach						();

	void CameraLookAt				(const Transform& target_);	
	void CameraLookAt				(const ddd::Vector3& target_);
	void LookAt						(const Transform& target_);
	void LookAt						(const ddd::Vector3& target_);
	void LookAt						(const ddd::Vector3& target_, const ddd::Vector3& facing_, const ddd::Vector3& up_);

	void Reset						();
	void ResetFlag					();
	void SetUpdateFlag				();

	void RotateTowards				(const Transform& target_, float rate);
	void RotateTowards				(const ddd::Vector3& target_, float rate);
	void RotateTowardsIgnoreHeight	(const Transform& target_, float rate);
	void RotateTowardsIgnoreHeight	(const ddd::Vector3& target_, float rate);
	void Slerp						(const ddd::Quaternion& q, float deltatime_);

	void ForceUpdate				();
	void Update						();
	void dump						() const;

	// ____________________________________________________________ serial
#ifdef TINYXML2_EXPORT
	void Serial		(FXMLDocument* doc, FXMLNode* pElem);
	void Unserial	(FXMLElement* pElem);
#endif

	//____________________________________________________________serial friend
	friend Transform ConcatVQS		(const Transform& t2_, const Transform& t1_);
	friend Transform ConcatLocalVQS	(const Transform& t2_, const Transform& t1_);

	ddd::Vector3		position;		//read-only
	ddd::Vector3		localPosition;	//read-only
	ddd::Vector3		scale;			//read-only
	ddd::Vector3		localScale;		//read-only
	ddd::Quaternion	rotation;		//read-only
	ddd::Quaternion	localRotation;	//read-only

private:
	std::vector<Transform*> child;
	int flags;
	ddd::Vector3 facing;
	Transform* parent;
	ddd::Matrix44 worldMatrix;

	void SignalChildDirtyBit();
};

// ____________________________________________________________ extern function
Transform InterpolateTransforms(const Transform& oldTransform, const Transform& newTransform, float factor);
void RotateTowards(Transform& transform_, const Transform& target, float rate);
void RotateTowards(Transform& transform_, const ddd::Vector3& target, float rate);

}

#endif //DDD_TRANSFORM_H_
