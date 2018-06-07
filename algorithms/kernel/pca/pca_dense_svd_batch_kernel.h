/* file: pca_dense_svd_batch_kernel.h */
/*******************************************************************************
* Copyright 2014-2018 Intel Corporation
* All Rights Reserved.
*
* If this  software was obtained  under the  Intel Simplified  Software License,
* the following terms apply:
*
* The source code,  information  and material  ("Material") contained  herein is
* owned by Intel Corporation or its  suppliers or licensors,  and  title to such
* Material remains with Intel  Corporation or its  suppliers or  licensors.  The
* Material  contains  proprietary  information  of  Intel or  its suppliers  and
* licensors.  The Material is protected by  worldwide copyright  laws and treaty
* provisions.  No part  of  the  Material   may  be  used,  copied,  reproduced,
* modified, published,  uploaded, posted, transmitted,  distributed or disclosed
* in any way without Intel's prior express written permission.  No license under
* any patent,  copyright or other  intellectual property rights  in the Material
* is granted to  or  conferred  upon  you,  either   expressly,  by implication,
* inducement,  estoppel  or  otherwise.  Any  license   under such  intellectual
* property rights must be express and approved by Intel in writing.
*
* Unless otherwise agreed by Intel in writing,  you may not remove or alter this
* notice or  any  other  notice   embedded  in  Materials  by  Intel  or Intel's
* suppliers or licensors in any way.
*
*
* If this  software  was obtained  under the  Apache License,  Version  2.0 (the
* "License"), the following terms apply:
*
* You may  not use this  file except  in compliance  with  the License.  You may
* obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*
* Unless  required  by   applicable  law  or  agreed  to  in  writing,  software
* distributed under the License  is distributed  on an  "AS IS"  BASIS,  WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
* See the   License  for the   specific  language   governing   permissions  and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Declaration of template structs that calculate PCA SVD.
//--
*/

#ifndef __PCA_DENSE_SVD_BATCH_KERNEL_H__
#define __PCA_DENSE_SVD_BATCH_KERNEL_H__

#include "pca_batch.h"
#include "pca_types.h"
#include "svd/svd_dense_default_kernel.h"

#include "pca_dense_svd_base.h"

namespace daal
{
namespace algorithms
{
namespace pca
{
namespace internal
{

template <typename algorithmFPType, CpuType cpu>
class PCASVDBatchKernel : public PCASVDKernelBase<algorithmFPType, cpu>
{
public:
    PCASVDBatchKernel() {};

    services::Status compute(InputDataType type, const data_management::NumericTablePtr &data,
        data_management::NumericTable &eigenvalues, data_management::NumericTable& eigenvectors);

    services::Status compute(InputDataType type,
            data_management::NumericTable& data,
            const BatchParameter<algorithmFPType, svdDense>* parameter,
            data_management::NumericTable& eigenvalues,
            data_management::NumericTable& eigenvectors,
            data_management::NumericTable& means,
            data_management::NumericTable& variances);

protected:
    services::Status normalizeDataset(const data_management::NumericTablePtr& data, data_management::NumericTablePtr& normalizedData);

    services::Status decompose(const NumericTable *normalizedDataTable, data_management::NumericTable& eigenvalues,
        data_management::NumericTable& eigenvectors);
};

} // namespace internal
} // namespace pca
} // namespace algorithms
} // namespace daal
#endif