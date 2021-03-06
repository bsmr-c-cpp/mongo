/**
 *    Copyright (C) 2014 MongoDB Inc.
 *
 *    This program is free software: you can redistribute it and/or  modify
 *    it under the terms of the GNU Affero General Public License, version 3,
 *    as published by the Free Software Foundation.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Affero General Public License for more details.
 *
 *    You should have received a copy of the GNU Affero General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the GNU Affero General Public License in all respects for
 *    all of the code used other than as permitted herein. If you modify file(s)
 *    with this exception, you may extend this exception to your version of the
 *    file(s), but you are not obligated to do so. If you do not wish to do so,
 *    delete this exception statement from your version. If you delete this
 *    exception statement from all source files in the program, then also delete
 *    it in the license file.
 */

#pragma once

#include <stdlib.h>

#include "mongo/base/disallow_copying.h"

namespace mongo {

    /**
     * This name and this class are both a work in progress.
     */
    class TransactionExperiment  {
        MONGO_DISALLOW_COPYING(TransactionExperiment);
    public:
        virtual ~TransactionExperiment() { }

        /**
         * Commit if required.  May take a long time.  Returns true if committed.
         */
        virtual bool commitIfNeeded(bool force = false) = 0;

        /**
         * Returns true if a commit is needed but does not commit.
         */
        virtual bool isCommitNeeded() const = 0;

        /**
         * Declare that the data at [x, x + len) is being written.
        */
        virtual void writingPtr(void* data, size_t len) = 0;

        /**
         * A templated helper for writingPtr.
         */
        template <typename T>
        inline T* writing(T* x) {
            return static_cast<T*>(writingPtr(x, sizeof(T)));
        }
    };

}  // namespace mongo
