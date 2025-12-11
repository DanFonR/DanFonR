from typing import NoReturn
from numpy import float64, array
from numpy.linalg import norm
from numpy.typing import NDArray

def proj(v1: NDArray[float64],
		 v2: NDArray[float64]) -> NDArray[float64]:
	"""
	Projects a vector `v1` over a vector `v2`

	:param v1: Vector to be projected (n,)
	:type v1: NDArray[float64]

	:param v2: Vector to be projected upon (n,)
	:type v2: NDArray[float64]

	:return: The projection of `v1` over `v2`
	:rtype: ndarray[float64]
	"""

	if len(v1.shape) != 1 or len(v2.shape) != 1:
		raise ValueError("vector has incorrect shape (n,m) instead of (n,)")

	dot_upper: float64 = v1.dot(v2)
	dot_v2: float64 = v2.dot(v2)

	return (dot_upper/dot_v2) * v2


def gs_ort(arr: NDArray[float64],
		   normalize: bool = True) -> NDArray[float64]:
	"""
	Performs Gram-Schmidt Orthogonalization/Orthonormalization

	:param arr: The vector matrix (each vector as a column matrix)
	:type arr: NDArray[float64]

	:param normalize: Whether to normalize the resulting vectors or not
	:type normalize: bool

	:return: The orthogonal/orthonormal vectors as a matrix
	:rtype: ndarray[float64]
	"""

	init: NDArray[float64] = arr[:,0].astype(float64)

	if normalize:
		init /= norm(init)

	res: list[NDArray[float64]] = [init]

	for i in range(1, len(arr)):
		sum_array: NDArray[float64] = sum(
			proj(arr[:,i], res[j]) for j in range(len(res))
		)
		temp: NDArray[float64] = arr[:,i] - sum_array

		if normalize:
			temp /= norm(temp)

		res.append(temp)

	gs_mat: NDArray[float64] = array(res).T

	return gs_mat

def main() -> NoReturn:
	A: NDArray[float64] = array([[3, 2], [1, 2]])
	B: NDArray[float64] = gs_ort(A)
	print(B)

if __name__ == "__main__":
	main()
